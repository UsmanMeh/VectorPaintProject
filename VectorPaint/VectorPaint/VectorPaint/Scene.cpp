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
		mEntityManager = new ECS::ECSManager();
		mCommandManager = new CommandManager();
		std::cout << "Scene::Initialize(" << Name << ")" << std::endl;
	}
	void Scene::Update()
	{
		mEntityManager->Update();
		//std::cout << "Scene::Update(" << Name << ")" << std::endl; 
	}
	void Scene::Render()
	{
		mEntityManager->Render();
		//std::cout << "Scene::Render(" << Name << ")" << std::endl;
	}
	void Scene::RenderGUI()
	{
		//std::cout << "Scene::RenderGUI(" << Name << ")" << std::endl;
	}
	void Scene::Clean()
	{
		delete mEntityManager;
		std::cout << "Scene::Clean(" << Name << ")" << std::endl;
	}

	ECS::Entity& Scene::CreateNewEntity()
	{
		return mEntityManager->AddEntity();
	}
