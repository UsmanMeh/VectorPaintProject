#pragma once
#include <iostream>
#include <glad/glad.h>
#include <SDL.h>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <array>
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Rect.h"
enum class ShaderType : std::size_t
{
	PlygonShader,
	LineShader,
	CircleShader,
	Size
};
class Renderer
{
private:
	Window* mWindow;
	const int viewPortWidth = 1920;
	const int viewportHeight = 1080;
public:

	std::array<Shader*, static_cast<size_t>(ShaderType::Size)> shaders;
	bool Initialize(Window* pWindow)
	{
		mWindow = pWindow;
		shaders[(int)(ShaderType::PlygonShader)] = (new Shader("vertex_shader.glsl", "polygon_fragment_shader.glsl"));
		shaders[(int)(ShaderType::LineShader)] = (new Shader("vertex_shader.glsl", "line_fragment_shader.glsl"));
		shaders[(int)(ShaderType::CircleShader)] = (new Shader("vertex_shader.glsl", "circle_fragment_shader.glsl"));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Camera::aspactRatio = (float)viewPortWidth / (float)viewportHeight;
		return true;
	}
	void Update() {
	}
	void PreRender(Window* pWindow)
	{
		mWindow = pWindow;
		glViewport(mWindow->Width/2- viewPortWidth/2, mWindow->Height/2 - viewportHeight/2, viewPortWidth, viewportHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, viewPortWidth, viewportHeight, 0, -5, 5);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Render(SDL_Window* SDLWindow)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS); glVertex3i(0, 0, 0); glVertex3i(viewPortWidth, 0, 0); glVertex3i(viewPortWidth, viewportHeight, 0); glVertex3i(0, viewportHeight, 0); glEnd();
	}
	void PostRender(SDL_Window* SDLWindow)
	{
		SDL_GL_SwapWindow(SDLWindow);
	}
	Rect GetViewportRect()
	{
		return Rect(mWindow->Width / 2 - viewPortWidth / 2, mWindow->Height / 2 - viewportHeight / 2, viewPortWidth, viewportHeight);
	}
	const Window* GetWindow()
	{
		return mWindow;
	}
};

