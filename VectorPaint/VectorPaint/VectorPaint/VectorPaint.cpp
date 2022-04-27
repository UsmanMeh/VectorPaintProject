#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "glad/glad.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace std;

int windowHight = 900;
int windowWidth = 1200;
bool initGLShaders();
void render();
void logic();
struct attributes {
	GLfloat coord3d[3];
	GLfloat v_color[3];
};

SDL_Window* window = nullptr;

GLuint program;
GLint attribute_coord3d;
GLint uniform_m_transform;
GLuint vbo_triangle;

int main(int argc, char* argv[])
{
	//init SDL and early out if we have issue with SDL init


	//setup SDL screen, window and renderer
	SDL_Surface* screen;
	SDL_Renderer* renderer = NULL;
	SDL_GLContext context;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not init" << SDL_GetError();
		return 0;
	}
	else
	{
		cout << "SDL is Init and ready";
	}
	//initialize SDL screen, window and renderer
	int flags = 0;
	flags = SDL_WINDOW_RESIZABLE| SDL_WINDOW_OPENGL;

	window = SDL_CreateWindow("STL Test Window", 0, 200, windowWidth, windowHight, flags);
	screen = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//SDL_UpdateWindowSurface(window);

	//init GL contect

	context = SDL_GL_CreateContext(window);
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	initGLShaders();

	 //simple test code to test SDL events and rendering.

	bool running = true;
	bool dragStart = false;
	bool dragEnd = false;
	pair <int, int > startClick;
	pair <int, int > endClick;
	pair <int, int > currentMousePos;
	while (running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
		}
		logic();
		render();
		 
	}
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo_triangle);
	SDL_Quit();

	//cout << "hello world";
	return 0;

}
bool initGLShaders()
{
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	// setting up vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vs_source =
		//"#version 100\n"  // OpenGL ES 2.0
		"#version 120\n"  // OpenGL 2.1
		"attribute vec3 coord3d;                  "
		"uniform mat4 m_transform;                 "
		"void main(void) {                        "
		"  gl_Position = m_transform * vec4(coord3d, 1.0); "
		"}";
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		std::cout << "Error in vertex shader" << std::endl;
		return false;
	}

	//setting up frag shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fs_source =
		//"#version 100\n"  // OpenGL ES 2.0
		"#version 120\n"  // OpenGL 2.1
		"void main(void) {        "
		"gl_FragColor[0] = gl_FragCoord.x / 1080.0;"
		"gl_FragColor[1] = gl_FragCoord.y / 1080.0;"
		"gl_FragColor[2] = 0.5; "
		"gl_FragColor[3] = 1.0;"
		"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		std::cout << "Error in fragment shader" << std::endl;
		return false;
	}

	// create program and attaching shaders
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		std::cout << "Error in glLinkProgram" << std::endl;
		return false;
	}
	/* init_resources() */
	const char* attribute_name = "coord3d";
	attribute_coord3d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord3d == -1) {
		cerr << "Could not bind attribute " << attribute_name << endl;
		return false;
	}
	const char* uniform_name = "m_transform";
	uniform_m_transform = glGetUniformLocation(program, uniform_name);
	if (uniform_m_transform == -1) {
		cerr << "Could not bind uniform " << uniform_name << endl;
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "\nShaders Init Complete." << std::endl;
	return true;
}
void logic() {
	float move = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5);
	float angle = SDL_GetTicks() / 1000.0 * 45;
	glm::vec3 axis_z(0, 0, 1);
	glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(move, 0.0, 0.0))
		* glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_z);
	glUseProgram(program);
	glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
}
void render()
{
	/* Clear the background as white */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	float size = 0.4f;
	GLfloat rect_vertices[] = {
		-1.0 * size,  -1.0 * size,
		-1.0 * size, 1.0 * size,
		1.0 * size, 1.0 * size,
		-1.0 * size, -1.0 * size,
		1.0 * size, 1.0 * size,
		1.0 * size, -1.0 * size,
	};

	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord3d);
	glVertexAttribPointer(
		attribute_coord3d,   // attribute
		2,                   // number of elements per vertex, here (x,y,z)
		GL_FLOAT,            // the type of each element
		GL_FALSE,            // take our values as-is
		0,					 // next coord3d appears every 6 floats
		rect_vertices        // vertex array pointer
	);
	
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(attribute_coord3d);

	//std::cout <<"GL Error = " << glGetError() << std::endl;

	SDL_GL_SwapWindow(window);
}
