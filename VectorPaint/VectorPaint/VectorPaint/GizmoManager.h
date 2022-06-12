#pragma once
#include <array>
#include "LineGizmo.h"
#include "RectGizmo.h"
#include "ToolsManager.h"
class GizmoManager
{
private:
	static GizmoManager * instance;
	//static std::array<Gizmo*, (int)ToolsManager::Tools::size> Gizmos;
	static std::array<Gizmo*, 1> Gizmos;
	static bool isEntitySelected;
public:
	static GizmoManager* GetInstance();

	static void Initialize();
	static void Update();
	static void DrawGizmo();
	static void Clean();
	static void OnMouseDown(bool pLeftButton, Vector2D pPos);
	static void OnMouseUp(bool pLeftButton , Vector2D pPos);
	static void MousePositionUpdate(Vector2D pos);
	static void EntitySelected(std::shared_ptr<ECS::Entity> pSelectedEntity);
	static void EntityUnSelected();
	static bool SelectControlPoint(Vector2D pPoint);

};