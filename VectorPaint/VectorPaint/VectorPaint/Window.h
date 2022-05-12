#pragma once
#include <iostream>
#include <SDL.h>
#include "glad/glad.h"
class Window
{
public:
	int Height = 900;
	int Width = 900;

	int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED;

	SDL_Window* SDLWindow = nullptr;
	SDL_GLContext GLContext = nullptr;
	Uint32 windowID;

	bool Initialize();
	void Clean();

};

