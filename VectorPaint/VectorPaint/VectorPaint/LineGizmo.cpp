#include "LineGizmo.h"
void LineGizmo::Initialize() 
{
	
}
void LineGizmo::Update(){}
void LineGizmo::DrawGizmo() 
{
	for (size_t i = 0; i < mControlPoints.size(); i++)
	{
		mControlPoints[i].Draw();
	}
}
void LineGizmo::OnMouseDown(bool pLeftButton, Vector2D pPos)
{
	mControlPoints[0].SetPosition(pPos);
}

void LineGizmo::OnMouseUp(bool pLeftButton, Vector2D pPos)
{
}

void LineGizmo::MousePositionUpdate(Vector2D pPos)
{
	mControlPoints[1].SetPosition(pPos);
}

void LineGizmo::EntitySelected(std::shared_ptr<ECS::Entity> pSelectedEntity)
{

}