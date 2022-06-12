#pragma once
#include <array>
#include "Gizmo.h"
#include "ControlPoint.h"
class RectGizmo :public Gizmo
{
private:
	std::array <ControlPoint, 4> mControlPoints;
public:
	void Initialize() override;
	void Update() override;
	void DrawGizmo() override;
	void OnMouseDown(bool pLeftButton, Vector2D pPos) override;
	void OnMouseUp(bool pLeftButton, Vector2D pPos) override;
	void MousePositionUpdate(Vector2D pos) override;
	bool SelectControlPoint(Vector2D pPos) override;
	void EntitySelected(std::shared_ptr<ECS::Entity> pSelectedEntity)override;
};