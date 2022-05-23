#include "Manager.h"
#include "GUIManager.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <imgui_internal.h>
#include <vec4.hpp>
#include "Camera.h"

bool GUIManager::Initialize(Window* p_window)
{
	window = p_window;
	mToolsManager = ToolsManager::GetInstance();
	Debug::Initialize();
	const char* glsl_version = "#version 120";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	fillColor[0] = 0;
	fillColor[1] = 0;
	fillColor[2] = .5;
	fillColor[3] = 1;

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window->SDLWindow, window->GLContext);
	ImGui_ImplOpenGL3_Init(glsl_version);
    return false;
}
bool 
square = true,
circle = false, 
rectangle = false,
triangle = false;
void GUIManager::RenderGUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	SetDockSpace();
    ShowMenuBar();
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Tools");

	for (int tool = ToolsManager::Tools::Selection; tool != ToolsManager::Tools::size; tool++)
	{
	    if(ImGui::RadioButton(mToolsManager->ToolsNameList[static_cast<ToolsManager::Tools>(tool)].c_str(), static_cast<ToolsManager::Tools>(tool) == mToolsManager->GetSelectedTool()))
		{
			mToolsManager->ToolsList[static_cast<ToolsManager::Tools>(tool)] = true;
			mToolsManager->SetSelectedTool(static_cast<ToolsManager::Tools>(tool));
		}
	}
	if (ImGui::Button("ResetCamera"))
	{
		Camera::x = 0;
		Camera::y = 0;
	}
	ImGui::End();
	
	ImGui::SetNextItemWidth(500);
	ImGui::Begin("Color Selection");
	ImGui::ColorPicker4("Select color", fillColor , ImGuiColorEditFlags_DisplayRGB  | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview);
	const ImVec4 col_v4(fillColor[0], fillColor[1], fillColor[2], fillColor[3]);
	ImGui::SetNextItemWidth(500);
	ImGui::ColorButton("Test Color Button", col_v4);
	mToolsManager->SetCurrentColor(glm::vec4(fillColor[0], fillColor[1], fillColor[2] , fillColor[3]));
	ImGui::End();

	Debug::RenderGUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//SDL_GL_SwapWindow(window->SDLWindow);
}
void GUIManager::SetDockSpace()
{
	//Flags for dock space and dock space window
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	//Setting window size for dock space window.
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	//Set Window styls for the dock window
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	//Set window flags for dock window so we have no visuals for the windwo 
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;
	//set the dock space flags so it is pass through and no window can be docked on scene area 
	dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
	// create dock space window and assign the dock space to it.

	bool open = false;

	// Submit the dock space
	ImGui::Begin("DockSpace", &open, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);
	dockspace_id = ImGui::GetID("MainDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

	ImGui::End();
}
void GUIManager::Clean()
{
	Debug::Clean();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void GUIManager::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ShowMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) 
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
void GUIManager::ShowMenuFile()
{
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}
    ImGui::Separator();
	if (ImGui::MenuItem("Quit", "Alt+F4")) 
	{
		Manager::GetInstance()->ApplicationState = Manager::ApplicationStates::Quitting;
	}
}
