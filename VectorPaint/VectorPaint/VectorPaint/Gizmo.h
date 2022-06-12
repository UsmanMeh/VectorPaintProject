#pragma once
#include "Vector2D.h"
#include "ECS.h"
class Gizmo
{
protected:
	int mSelectedCPIndex = -1; // index for the selected CP or -1 if non selected. 
public:
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void DrawGizmo() {}
	virtual void OnMouseDown(bool pLeftButton, Vector2D pPos) {}
	virtual void OnMouseUp(bool pLeftButton, Vector2D pPos) {}
	virtual void MousePositionUpdate(Vector2D pos) {}
	virtual bool SelectControlPoint(Vector2D pPos) { return false; }
	virtual void EntitySelected(std::shared_ptr<ECS::Entity> pSelectedEntity) {}
};

