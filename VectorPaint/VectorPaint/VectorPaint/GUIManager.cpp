#include "Manager.h"
#include "GUIManager.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <imgui_internal.h>

float fillColor[] = { 1,1,1,1 };
bool GUIManager::Initialize(Window* p_window)
{
	window = p_window;
	const char* glsl_version = "#version 120";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window->SDLWindow, window->GLContext);
	ImGui_ImplOpenGL3_Init(glsl_version);
    return false;
}

void GUIManager::RenderGUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	SetDockSpace();
    ShowMenuBar();
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Tools");

	//selection = ImGui::RadioButton("Selection Tool", selection);
	//circle = ImGui::RadioButton("Circle Tool", circle);
	//rectangle = ImGui::RadioButton("rectangle Tool", rectangle);
	//triangle = ImGui::RadioButton("triangle Tool", triangle);

	ImGui::End();

	ImGui::Begin("Color Selection");
	ImGui::ColorPicker4("Select color", fillColor , ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float);
	ImGui::End();


	ImGui::Begin("Debug Window");
	ImGui::Text("Debug Window");
	ImGui::End();
	ImGui::Begin("ViewPort");
	ImGui::End();

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
	//static auto first_time = true;
	//if (first_time)
	//{
	//	first_time = false;

	//	ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
	//	ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_None); // Add empty node
	//	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	//	ImGuiID dockMainId = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
	//	ImGuiID dockIdLeft = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Left, 0.10f, NULL, &dockMainId);
	//	ImGuiID dockIdBottom = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Down, 0.20f, NULL, &dockMainId);
	//	ImGuiID dockIdLeftBottom = ImGui::DockBuilderSplitNode(dockIdLeft, ImGuiDir_Down, 0.20f, NULL, &dockMainId);

	//	ImGui::DockBuilderDockWindow("ViewPort", dockMainId);
	//	ImGui::DockBuilderDockWindow("Tools", dockIdLeft);
	//	ImGui::DockBuilderDockWindow("Color Selection", dockIdLeftBottom);
	//	ImGui::DockBuilderDockWindow("Debug Window", dockIdBottom);
	//	ImGui::DockBuilderFinish(dockspace_id);
	//}
	ImGui::End();
}
void GUIManager::Clean()
{
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
