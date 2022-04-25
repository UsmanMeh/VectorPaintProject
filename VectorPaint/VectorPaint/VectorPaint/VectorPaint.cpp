#include <stdio.h>
#include <iostream>
#include <SDL.h>
using namespace std;

int windowHight = 900;
int windowWidth = 1200;

void DrawRect(SDL_Renderer* renderer, pair <int, int > startClick, pair <int, int > endClick)
{
	SDL_Rect rect;
	rect.x = startClick.first;
	rect.y = startClick.second;
	rect.w = endClick.first - startClick.first;
	rect.h = endClick.second - startClick.second;
	SDL_RenderDrawRect(renderer, &rect);
}
int main(int argc, char* argv[])
{
	//init SDL and early out if we have issue with SDL init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not init" << SDL_GetError();
		return;
	}
	else
	{
		cout << "SDL is Init and ready";
	}

	//setup SDL screen, window and renderer
	SDL_Surface* screen;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = NULL;

	//initialize SDL screen, window and renderer
	window = SDL_CreateWindow("STL Test Window", 0, 200, windowWidth, windowHight, SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_UpdateWindowSurface(window);

	// simple test code to test SDL events and rendering.

	bool running = true;
	bool dragStart = false;
	bool dragEnd = false;
	pair <int, int > startClick;
	pair <int, int > endClick;
	pair <int, int > currentMousePos;
	while (running)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				cout << "\n";
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					cout << "Left";
					SDL_GetMouseState(&startClick.first, &startClick.second);
					dragStart = true;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT)
					cout << "Right";
				cout << " Click DOWN";
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				cout << "\n";
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					cout << "Left";
					dragEnd = true;
					dragStart = false;
					SDL_GetMouseState(&endClick.first, &endClick.second);

				}
				else if (event.button.button == SDL_BUTTON_RIGHT)
					cout << "Right";
				cout << " Click Up";
			}

		}
		if (dragStart)
		{
			SDL_GetMouseState(&currentMousePos.first, &currentMousePos.second);
			DrawRect(renderer, startClick, currentMousePos);
		}
		else if (dragEnd)
		{
			DrawRect(renderer, startClick, endClick);
		}
		SDL_RenderPresent(renderer);

	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	//cout << "hello world";
	return 0;

}
