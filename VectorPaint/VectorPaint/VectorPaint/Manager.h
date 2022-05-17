#pragma once
#include "SceneManager.h"
#include "Window.h"
#include "GUIManager.h"
#include "Renderer.h"
#include "MouseController.h"
class Manager
{
private:
	static Manager* instance;
	SceneManager sceneManager;
	MouseController mouseController;
	Window window;
	Renderer renderer;
	GUIManager guiManager;
	SDL_Event event;
public:
	enum class ApplicationStates {Running , InBackground , Paused , Quitting } ApplicationState = ApplicationStates::Running;
	static Manager* GetInstance();

	void Initialize();
	void Update();
	void Render();
	void RenderGUI();
	void Clean();
	Renderer* GetRenderer();
	Window* GetWindow();
};

