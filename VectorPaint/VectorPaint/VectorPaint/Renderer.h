#pragma once
#include <iostream>
#include <glad/glad.h>
#include <SDL.h>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Renderer
{
public:
	GLuint program;
	GLint attribute_coord3d;
	GLint uniform_m_transform;
	bool Initialize()
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
			std::cout << "Could not bind attribute " << attribute_name << std::endl;
			return false;
		}
		const char* uniform_name = "m_transform";
		uniform_m_transform = glGetUniformLocation(program, uniform_name);
		if (uniform_m_transform == -1) {
			std::cout << "Could not bind uniform " << uniform_name << std::endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::cout << "\nShaders Init Complete." << std::endl;
		return true;
	}
	void Update() {
		float move = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5);
		float angle = SDL_GetTicks() / 1000.0 * 45;
		glm::vec3 axis_z(0, 0, 1);
		glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(move, 0.0, 0.0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_z);
		glUseProgram(program);
		glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
	}
	void PreRender()
	{
		glViewport(500, 0, 900, 900);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Render(SDL_Window* SDLWindow)
	{
		float size = 0.1f;
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
		
	}
	void PostRender(SDL_Window* SDLWindow)
	{
		SDL_GL_SwapWindow(SDLWindow);
	}
};

