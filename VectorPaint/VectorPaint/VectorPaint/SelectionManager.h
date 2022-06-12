#pragma once
#include <vector>
#include "ECSManager.h"
class SelectionManager
{
private:
	ECS::ECSManager * mEntityManager;
	std::vector<std::shared_ptr<ECS::Entity>> mSelectedEntities;
public: 
	SelectionManager(ECS::ECSManager* pEntitymanager) : mEntityManager(pEntitymanager) {};
	void Initialize();
	void Update();
	void Render();
	void RenderGUI();
	void Clean();

	void SelectEntity(Vector2D pPoint);
};

