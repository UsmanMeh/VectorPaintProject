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
	mMouseController = new MouseController();
	mKeyboardController = new KeyboardController();
	mDrawingManager = new DrawingManager();
	mSceneManager = new SceneManager();
	window.Initialize();
	renderer.Initialize(&window);
	mSceneManager->Initialize();
	mMouseController->Initialize(mSceneManager->GetActvieScene(), &renderer);
	mKeyboardController->Initialize(mSceneManager);
	mDrawingManager->Initialize();
	guiManager.Initialize(&window);
	GizmoManager::GetInstance()->Initialize();
}

void Manager::UpdateEvent()
{
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
		{
			ApplicationState = ApplicationStates::Quitting;
			break;
		}
		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.windowID == window.windowID)
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					window.Width = event.window.data1;
					window.Height = event.window.data2;
					break;
				}
			}
		}
		mMouseController->UpdateEvent(event);
		mKeyboardController->UpdateEvent(event);
	}
}

void Manager::Update()
{

	mMouseController->Update();
	mKeyboardController->Update();
	GizmoManager::GetInstance()->Update();
	mSceneManager->Update();
	mDrawingManager->Update();
}
void Manager::Render()
{
	renderer.PreRender(&window);
	renderer.Render(window.SDLWindow);
	mSceneManager->Render();
	mMouseController->Render();
	mDrawingManager->Render();
	GizmoManager::GetInstance()->DrawGizmo();
}
void Manager::RenderGUI()
{
	guiManager.RenderGUI();
	mSceneManager->RenderGUI();
	renderer.PostRender(window.SDLWindow);
}
void Manager::Clean()
{
	GizmoManager::GetInstance()->Clean();
	guiManager.Clean();
	mSceneManager->Clean();
	window.Clean();

	//delete mMouseController;
	//delete mDrawingManager;
	//delete mSceneManager;
}
SceneManager* Manager::GetSceneManager()
{
	return mSceneManager;
}
Renderer* Manager::GetRenderer()
{
	return &renderer;
}
Manager::~Manager()
{
	delete mMouseController;
	delete mDrawingManager;
	delete mSceneManager;
	delete instance;
}
Manager::Manager()
{
}
Window* Manager::GetWindow()
{
	return &window;
}
MouseController* Manager::GetMouseController()
{
	return mMouseController;
}
KeyboardController* Manager::GetKeyboardController()
{
	return mKeyboardController;
}