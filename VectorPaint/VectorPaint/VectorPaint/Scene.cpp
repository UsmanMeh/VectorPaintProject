#include "Scene.h"
#include <iostream>
#include "ECS.h"
#include "TransformComponent.h"
#include "PolygonComponent.h"
#include "PolygonRendererSystem.h"
#include "AddPolygonCommand.h"
	Scene::Scene()
	{
		Name = "Default";
	}
	void Scene::Initialize()
	{
		entityManager = new ECS::ECSManager();
		commandManager = new CommandManager();
		std::cout << "Scene::Initialize(" << Name << ")" << std::endl;
		//Temp test for the adding new object through commands to the ECS manager.
		std::unique_ptr<AddPolygonCommand>  addPolyCmd;
		addPolyCmd = std::unique_ptr<AddPolygonCommand>(new AddPolygonCommand(entityManager, Vector2D(50, 50), Vector2D(50, 50)));
		commandManager->AddCommand(std::move(addPolyCmd));

	}
	void Scene::Update()
	{
		entityManager->Update();
		//std::cout << "Scene::Update(" << Name << ")" << std::endl; 
	}
	void Scene::Render()
	{
		entityManager->Render();
		//std::cout << "Scene::Render(" << Name << ")" << std::endl;
	}
	void Scene::RenderGUI()
	{
		//std::cout << "Scene::RenderGUI(" << Name << ")" << std::endl;
	}
	void Scene::Clean()
	{
		delete entityManager;
		std::cout << "Scene::Clean(" << Name << ")" << std::endl;
	}

	ECS::Entity& Scene::CreateNewEntity()
	{
		return entityManager->AddEntity();
	}
