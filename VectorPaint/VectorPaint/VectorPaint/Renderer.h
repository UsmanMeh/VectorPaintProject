#pragma once
#include <iostream>
#include <glad/glad.h>
#include <SDL.h>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Window.h"
#include "Rect.h"

class Renderer
{
private:
	Window* mWindow;
	const int viewPortWidth = 1024;
	const int viewportHeight = 680;
public:
	GLuint program;
	GLint attribute_coord3d;
	GLint uniform_m_transform;
	Shader* shader;
	bool Initialize()
	{
		shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}
	void Update() {
	}
	void PreRender(Window* pWindow)
	{
		mWindow = pWindow;
		glViewport(mWindow->Width/2- viewPortWidth/2, mWindow->Height/2 - viewportHeight/2, viewPortWidth, viewportHeight);
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(0, viewPortWidth, viewportHeight, 0, -5, 5);
		//glMatrixMode(GL_MODELVIEW);
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Render(SDL_Window* SDLWindow)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS); glVertex3i(-1, -1, -1); glVertex3i(1, -1, -1); glVertex3i(1, 1, -1); glVertex3i(-1, 1, -1); glEnd();
	}
	void PostRender(SDL_Window* SDLWindow)
	{
		SDL_GL_SwapWindow(SDLWindow);
	}
	Rect GetViewportRect()
	{
		return Rect(mWindow->Width / 2 - viewPortWidth / 2, mWindow->Height / 2 - viewportHeight / 2, viewPortWidth, viewportHeight);
	}
};

