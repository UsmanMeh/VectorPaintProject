#include "Manager.h"
#include <imgui_impl_sdl.h>

Manager* Manager::instance = nullptr;
Manager* Manager::GetInstance()
{
	if (!instance)
		instance = new Manager;
	return instance;
}

void Manager::Initialize()
{
	window.Initialize();
	guiManager.Initialize(&window);
	renderer.Initialize();
	sceneManager.Initialize();
	mouseController.Initialize(sceneManager.GetActvieScene(), &renderer);
}
void Manager::Update()
{
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
		{
			ApplicationState = ApplicationStates::Quitting;
			break;
		}
		if(event.type == SDL_WINDOWEVENT)
		{
			if (event.window.windowID == window.windowID)
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					window.Width = event.window.data1;
					window.Height = event.window.data2;
					glViewport(window.Width / 4, window.Height * 0.05f, window.Width / 2, window.Height - window.Height * 0.1f);
					break;
				}
			}
		}
		mouseController.UpdateEvent(event);
	}
	//renderer.Update();
	sceneManager.Update();
}
void Manager::Render()
{
	renderer.PreRender(&window);
	renderer.Render(window.SDLWindow);
	mouseController.Render();
	sceneManager.Render();
}
void Manager::RenderGUI()
{
	guiManager.RenderGUI();
	sceneManager.RenderGUI();
	renderer.PostRender(window.SDLWindow);
}
void Manager::Clean()
{
	guiManager.Clean();
	sceneManager.Clean();
	window.Clean();
}
Renderer* Manager::GetRenderer()
{
	return &renderer;
}
Window* Manager::GetWindow()
{
	return &window;
}