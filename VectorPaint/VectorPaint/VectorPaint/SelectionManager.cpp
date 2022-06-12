#include "SelectionManager.h"
#include "ECSManager.h"
#include "Debug.h"
#include "GizmoManager.h"
void SelectionManager::Initialize()
{}
void SelectionManager::Update()
{}
void SelectionManager::Render() 
{}
void SelectionManager::RenderGUI() 
{}
void SelectionManager::Clean() 
{
	mSelectedEntities.clear();
	GizmoManager::GetInstance()->EntityUnSelected();
}
void SelectionManager::SelectEntity(Vector2D pPoint)
{
	if(IsAnyEntitySelected()) //if we have an entity selected
	{
		if (!GizmoManager::SelectControlPoint(pPoint)) // we check if user is selecting the control point
		{
			Clean();
			SelectNewEntity(pPoint);
		}
	}
	else
	{
		SelectNewEntity(pPoint);
	}
}
std::shared_ptr<ECS::Entity> SelectionManager::GetSelectedEntity()
{
	return mSelectedEntities[0];
}
void SelectionManager::SelectNewEntity(Vector2D pPoint)
{
	mEntityManager->SelectEntity(mSelectedEntities, pPoint);
	if (IsAnyEntitySelected())
	{
		GizmoManager::EntitySelected(mSelectedEntities[0]);
		Debug::LogToConsole("Entity selected");
	}
}
bool SelectionManager::IsAnyEntitySelected()
{
	return mSelectedEntities.size() > 0;
}
