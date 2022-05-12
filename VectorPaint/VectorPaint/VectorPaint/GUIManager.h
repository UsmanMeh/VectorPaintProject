#pragma once
#include "Window.h"
#include "imgui.h"
class GUIManager
{
private:
	Window* window;
	ImGuiID dockspace_id;
	void SetDockSpace();
	void ShowMenuBar();
	void ShowMenuFile();
public:
	float fillColor[4];

	bool Initialize(Window* window);
	void RenderGUI();
	void Clean();
};

