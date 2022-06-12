#pragma once
#include <string>
#include "ECSManager.h"
#include "CommandManager.h"
#include "SelectionManager.h"
class Scene
{
public:
	ECS::ECSManager* mEntityManager;
	CommandManager* mCommandManager;
	SelectionManager* mSelectionManager;

	std::string Name;

	Scene();
	void Initialize();
	void Update();
	void Render();
	void RenderGUI();
	void Clean();

	ECS::Entity& CreateNewEntity();
};

