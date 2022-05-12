#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "glad/glad.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glm.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "Manager.h"

using namespace std;

int main(int argc, char* argv[])
{
	Manager* manager = Manager::GetInstance();
	//Initialize the Core classes
	manager->Initialize();
	while (manager->ApplicationState == Manager::ApplicationStates::Running)
	{
		manager->Update();
		manager->RenderGUI();
		manager->Render();
	}
	manager->Clean();
	return 0;
}
