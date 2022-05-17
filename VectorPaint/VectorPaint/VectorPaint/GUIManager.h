#pragma once
#include "Window.h"
#include "imgui.h"
#include "ToolsManager.h"
#include "Debug.h"
class GUIManager
{
private:
	Debug* debug;
	Window* window;
	ToolsManager* mToolsManager;
	ImGuiID dockspace_id;
	float fillColor[4];
	void SetDockSpace();
	void ShowMenuBar();
	void ShowMenuFile();
public:

	bool Initialize(Window* window);
	void RenderGUI();
	void Clean();
};

