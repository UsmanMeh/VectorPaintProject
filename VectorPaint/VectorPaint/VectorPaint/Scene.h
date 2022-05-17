#pragma once
#include <string>
#include "ECSManager.h"
#include "CommandManager.h"
class Scene
{
public:
	ECS::ECSManager* mEntityManager;
	CommandManager* mCommandManager;
	std::string Name;

	Scene();
	void Initialize();
	void Update();
	void Render();
	void RenderGUI();
	void Clean();

	ECS::Entity& CreateNewEntity();
};

