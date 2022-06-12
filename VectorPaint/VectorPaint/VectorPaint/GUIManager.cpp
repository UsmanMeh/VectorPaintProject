#include "Manager.h"
#include "GUIManager.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <imgui_internal.h>
#include <vec4.hpp>
#include "Camera.h"
const ImGuiViewport* viewport;

bool GUIManager::Initialize(Window* p_window)
{
	window = p_window;
	mToolsManager = ToolsManager::GetInstance();
	mCommandManager = Manager::GetInstance()->GetSceneManager()->GetActvieScene()->mCommandManager;
	Debug::Initialize();
	const char* glsl_version = "#version 120";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	fillColor[0] = 1;
	fillColor[1] = 1;
	fillColor[2] = 0;
	fillColor[3] = 1;

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window->SDLWindow, window->GLContext);
	ImGui_ImplOpenGL3_Init(glsl_version);
	viewport = ImGui::GetMainViewport();
	mToolButtonTextures.push_back(new Texture("IconPack/001-clicker.png", GL_TEXTURE_2D));
	mToolButtonTextures.push_back(new Texture("IconPack/002-line.png", GL_TEXTURE_2D));
	mToolButtonTextures.push_back(new Texture("IconPack/003-square.png", GL_TEXTURE_2D));
	mToolButtonTextures.push_back(new Texture("IconPack/004-rectangle.png", GL_TEXTURE_2D));
	mToolButtonTextures.push_back(new Texture("IconPack/005-triangle.png", GL_TEXTURE_2D));
	mToolButtonTextures.push_back(new Texture("IconPack/006-circle.png", GL_TEXTURE_2D));
	mToolButtonTextures.push_back(new Texture("IconPack/007-path.png", GL_TEXTURE_2D));
    return true;
}


void GUIManager::SetDockSpace()
{
	//Flags for dock space and dock space window
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	//Setting window size for dock space window.
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

void GUIManager::RenderGUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
    ShowMenuBar();
	SetDockSpace();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(ImVec2(64, viewport->WorkSize.y));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	bool open = true;
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Tools", &open, window_flags);
	int frame_padding = -1;                             // -1 == uses default padding (style.FramePadding)
	ImVec2 size = ImVec2(32.0f, 32.0f);                     // Size of the image we want to make visible
	ImVec2 uv0 = ImVec2(0.0f, 0.0f);                        // UV coordinates for lower-left
	ImVec2 uv1 = ImVec2(1.0f, 1.0f);// UV coordinates for (32,32) in our texture
	ImVec4 bg_col = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);         // Black background
	ImVec4 tint_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);       // No tint
	ToolsManager::Tools selectedTool = mToolsManager->GetSelectedTool();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
	//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
	for (int tool = ToolsManager::Tools::Selection; tool != ToolsManager::Tools::size; tool++)
	{
	  	if (static_cast<ToolsManager::Tools>(tool) == selectedTool)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.7f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.7f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.7f, 1.0f));
		}
		if (tool < mToolButtonTextures.size())
		{
			if (ImGui::ImageButton(mToolButtonTextures[tool]->GetImTextureID(), size, uv0, uv1, frame_padding, bg_col, tint_col))
			{
				mToolsManager->SetSelectedTool(static_cast<ToolsManager::Tools>(tool));
			}
		}
		if (static_cast<ToolsManager::Tools>(tool) == selectedTool)
		{
			ImGui::PopStyleColor(3);
		}
	}
	ImGui::PopStyleColor(2);
	
	ImGui::End();
	
	//ImGui::SetNextItemWidth(500);
	float pos[3] = {0.0f,0.0f,0.0f};
	ImGui::Begin("Properties");
	ImGui::InputFloat3("Position", pos);
	if (ImGui::Button("ResetCamera"))
	{
		Camera::SetCameraPosition(0.0f, 0.0f);
		Camera::SetCameraZoom(1.0);
	}

	ImGui::ColorPicker4("Select color", fillColor , ImGuiColorEditFlags_DisplayRGB  | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview);
	ImGui::End();

	const ImVec4 col_v4(fillColor[0], fillColor[1], fillColor[2], fillColor[3]);
	mToolsManager->SetCurrentColor(glm::vec4(fillColor[0], fillColor[1], fillColor[2] , fillColor[3]));
	ImGui::Begin("History");
	std::vector<std::string> commandHistoryDebugString;
	mCommandManager->GetDebugList(&commandHistoryDebugString);
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -10), false, ImGuiWindowFlags_HorizontalScrollbar);

	for (auto cmdString: commandHistoryDebugString)
		ImGui::TextWrapped(cmdString.c_str());

	ImGui::EndChild();

	ImGui::End();
	Debug::RenderGUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//SDL_GL_SwapWindow(window->SDLWindow);
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
