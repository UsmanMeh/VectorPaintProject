#pragma once
#include <string>
#include "ECSManager.h"
#include "CommandManager.h"
class Scene
{
	ECS::ECSManager* entityManager;
	CommandManager* commandManager;
public:
	std::string Name;

	Scene();
	void Initialize();
	void Update();
	void Render();
	void RenderGUI();
	void Clean();

	ECS::Entity& CreateNewEntity();
};

