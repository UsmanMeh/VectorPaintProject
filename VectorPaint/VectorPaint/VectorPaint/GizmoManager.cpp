#include "GizmoManager.h"


GizmoManager* GizmoManager::instance = nullptr;
std::array<Gizmo*, 1> GizmoManager::Gizmos{new RectGizmo()};
bool GizmoManager::isEntitySelected = false;
GizmoManager* GizmoManager::GetInstance()
{
	if (!instance)
		instance = new GizmoManager;
	return instance;
}
void GizmoManager::Initialize() 
{
}
void GizmoManager::Update() {}
void GizmoManager::DrawGizmo() 
{
	if (isEntitySelected)
	{
		for (size_t i = 0; i < Gizmos.size(); i++)
		{
			GizmoManager::Gizmos[i]->DrawGizmo();
		}
	}
}
void GizmoManager::Clean() {}


void GizmoManager::OnMouseDown(bool pLeftButton, Vector2D pPos)
{
	for (size_t i = 0; i < Gizmos.size(); i++)
	{
		GizmoManager::Gizmos[i]->OnMouseDown(pLeftButton, pPos);
	}
}

void GizmoManager::OnMouseUp(bool pLeftButton, Vector2D pPos)
{
	for (size_t i = 0; i < Gizmos.size(); i++)
	{
		GizmoManager::Gizmos[i]->OnMouseUp(pLeftButton, pPos);
	}
}

void GizmoManager::MousePositionUpdate(Vector2D pPos)
{
	for (size_t i = 0; i < Gizmos.size(); i++)
	{
		GizmoManager::Gizmos[i]->MousePositionUpdate(pPos);
	}
}
bool GizmoManager::SelectControlPoint(Vector2D pPos)
{
	for (size_t i = 0; i < Gizmos.size(); i++)
	{
		if (GizmoManager::Gizmos[i]->SelectControlPoint(pPos))
			return true;
	}
	return false;
}
void GizmoManager::EntitySelected(std::shared_ptr<ECS::Entity> pSelectedEntity)
{
	isEntitySelected = true;
	for (size_t i = 0; i < Gizmos.size(); i++)
	{
		GizmoManager::Gizmos[i]->EntitySelected(pSelectedEntity);
	}
}
void GizmoManager::EntityUnSelected()
{
	isEntitySelected = false;
}

