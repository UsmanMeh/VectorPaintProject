#include "Window.h"

bool Window::Initialize()
{
	//Set SDL open GL attributes
	//Using openGL 4.1 Loader with core profile.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Using double buffer rendering to avoid drawing on current buffer. 
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Init the SDL system
	// Fail safe in case SDL fails to initialize.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not Initialize" << SDL_GetError();
		return 0;
	}
	else
	{
		std::cout << "SDL is Initialize and ready";
	}

	SDLWindow = SDL_CreateWindow("Vector Painter.", 0, 200, Width, Height, flags);

	SDL_GL_MakeCurrent(SDLWindow, GLContext);
	// Enable vsync
	SDL_GL_SetSwapInterval(1);

	//init openGL context
	GLContext = SDL_GL_CreateContext(SDLWindow);
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	windowID = SDL_GetWindowID(SDLWindow);
	return 1;
}

void Window::Clean()
{
	SDL_DestroyWindow(SDLWindow);
	SDL_GL_DeleteContext(GLContext);
	SDL_Quit();
}
