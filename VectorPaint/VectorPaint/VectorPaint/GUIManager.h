#pragma once
#include "Window.h"
#include "imgui.h"
#include "ToolsManager.h"
#include "Debug.h"
#include "Texture.h"
class GUIManager
{
private:
	Debug* debug;
	Window* window;
	ToolsManager* mToolsManager;
	CommandManager* mCommandManager;
	ImGuiID dockspace_id;
	std::vector<Texture*> mToolButtonTextures;
	float fillColor[4];
	void SetDockSpace();
	void ShowMenuBar();
	void ShowMenuFile();
public:

	bool Initialize(Window* window);
	void RenderGUI();
	void Clean();
};

