#pragma once
#include <array>
#include "Gizmo.h"
#include "ControlPoint.h"
class LineGizmo :public Gizmo
{
private:
	std::array <ControlPoint, 2> mControlPoints;
public:
	void Initialize() override;
	void Update() override;
	void DrawGizmo() override;
	void OnMouseDown(bool pLeftButton, Vector2D pPos) override;
	void OnMouseUp(bool pLeftButton, Vector2D pPos) override;
	void MousePositionUpdate(Vector2D pos) override;
	void EntitySelected(std::shared_ptr<ECS::Entity> pSelectedEntity)override;
};