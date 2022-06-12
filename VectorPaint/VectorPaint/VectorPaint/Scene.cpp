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
		mSelectionManager = new SelectionManager(mEntityManager);
		mSelectionManager->Initialize();
		std::cout << "Scene::Initialize(" << Name << ")" << std::endl;
	}
	void Scene::Update()
	{
		mEntityManager->CleanUp();
		mEntityManager->Update();
	}
	void Scene::Render()
	{
		mEntityManager->Render();
	}
	void Scene::RenderGUI()
	{
	}
	void Scene::Clean()
	{
		mEntityManager->CleanUp();
		delete mSelectionManager;
		delete mCommandManager;
		delete mEntityManager;
	}

