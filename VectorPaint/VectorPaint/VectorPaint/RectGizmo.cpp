#include "RectGizmo.h"
#include "ColliderComponent.h"
#include "Camera.h"
void RectGizmo::Initialize()
{

}
void RectGizmo::Update() {}

void RectGizmo::DrawGizmo()
{
	glPushAttrib(GL_ENABLE_BIT);
	glLineStipple(1, 0xAAAA); 
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(mControlPoints[0].GetX(), mControlPoints[0].GetY());
	glVertex2f(mControlPoints[1].GetX(), mControlPoints[1].GetY());
	glVertex2f(mControlPoints[2].GetX(), mControlPoints[2].GetY());
	glVertex2f(mControlPoints[3].GetX(), mControlPoints[3].GetY());
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glPopAttrib();
	for (size_t i = 0; i < mControlPoints.size(); i++)
	{
		mControlPoints[i].Draw();
	}
}
void RectGizmo::OnMouseDown(bool pLeftButton, Vector2D pPos)
{
}

void RectGizmo::OnMouseUp(bool pLeftButton, Vector2D pPos)
{
}

void RectGizmo::MousePositionUpdate(Vector2D pPos)
{
}
bool RectGizmo::SelectControlPoint(Vector2D pPos)
{
	for (size_t i = 0; i < mControlPoints.size(); i++)
	{
		if (mControlPoints[i].Select(pPos))
		{
			if (mSelectedCPIndex != -1)
			{
				mControlPoints[mSelectedCPIndex].UnSelect();
			}
			mSelectedCPIndex = i;
			return true;
		}
	}
	if (mSelectedCPIndex != -1)
	{
		mControlPoints[mSelectedCPIndex].UnSelect();
	}
	mSelectedCPIndex = -1;
	return false;
}
void RectGizmo::EntitySelected(std::shared_ptr<ECS::Entity> pSelectedEntity)
{
	std::cout << "EntitySelected\n";
	Rect entityBB = pSelectedEntity->getComponent<ColliderComponent>()->GetBB();
	mControlPoints[0].SetPosition(entityBB.x, entityBB.y);
	mControlPoints[1].SetPosition(entityBB.x + entityBB.w, entityBB.y);
	mControlPoints[2].SetPosition(entityBB.x+ entityBB.w, entityBB.y + entityBB.h);
	mControlPoints[3].SetPosition(entityBB.x, entityBB.y + entityBB.h);
}