#pragma once
#include "SceneManager.h"
#include "Window.h"
#include "GUIManager.h"
#include "Renderer.h"
#include "MouseController.h"
#include "KeyboardController.h"
#include "GizmoManager.h"
#include "DrawingManager.h"
class Manager
{
private:
	static Manager* instance;
	SceneManager* mSceneManager;
	MouseController* mMouseController;
	KeyboardController* mKeyboardController;
	DrawingManager* mDrawingManager;
	Window window;
	Renderer renderer;
	GUIManager guiManager;
	SDL_Event event;
public:
	enum class ApplicationStates {Running , InBackground , Paused , Quitting } ApplicationState = ApplicationStates::Running;
	static Manager* GetInstance();

	Manager();
	~Manager();

	void Initialize();
	void Update();
	void UpdateEvent();
	void Render();
	void RenderGUI();
	void Clean();
	SceneManager* GetSceneManager();
	Renderer* GetRenderer();
	Window* GetWindow();
	MouseController* GetMouseController();
	KeyboardController* GetKeyboardController();
};

