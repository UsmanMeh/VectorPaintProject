#include "SelectionManager.h"
#include "ECSManager.h"
#include "Debug.h"
void SelectionManager::Initialize()
{}
void SelectionManager::Update()
{}
void SelectionManager::Render() 
{}
void SelectionManager::RenderGUI() 
{}
void SelectionManager::Clean() 
{}
void SelectionManager::SelectEntity(Vector2D pPoint)
{
	Debug::LogToConsole("try to selected");
	mSelectedEntities.clear();
	mEntityManager->SelectEntity(mSelectedEntities,pPoint);
	if(mSelectedEntities.size()>0)
	Debug::LogToConsole("Entity selected");
}
