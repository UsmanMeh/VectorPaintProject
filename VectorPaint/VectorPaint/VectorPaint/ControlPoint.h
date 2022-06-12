#pragma once
#include "Vector2D.h"
#include "Camera.h"
#include "Rect.h"
#include <glad/glad.h>
typedef long int* pint32;
class ControlPoint
{
private:
	float mPixelSize;
	float mSize;
	float mSelectedSize;
	Rect mBondingBox;
	Vector2D mPosition;
	bool mIsSelected;
public:
	ControlPoint()
	{
		mPixelSize = 5.0f;
		mSize = mPixelSize / 50;
		mSelectedSize = 10.0f;
		mIsSelected = false;
		mPosition = Vector2D(0.0f, 0.0f);
	};
	void ConvertToCameraSpace(Vector2D* point)
	{
		point->y -= Camera::y;
		point->x /= Camera::Zoom;
		point->y /= Camera::Zoom;
	}
	void SetPosition(Vector2D pPos)
	{
		/* test /**/
		mPosition = pPos;
		mBondingBox.SetStart(pPos.Subtract(mSize/2.0f));
		mBondingBox.w = mSize;
		mBondingBox.h = mSize;
		pint32 x, y, z;

	}
	void SetPosition(float pPosX, float pPosY)
	{
		SetPosition(Vector2D(pPosX, pPosY));
	}
	void UnSelect()
	{
		mIsSelected = false;
	}
	bool Select(Vector2D pPos)
	{
		if (pPos.x > mBondingBox.x && pPos.x < mBondingBox.x + mBondingBox.w &&
			pPos.y > mBondingBox.y && pPos.y < mBondingBox.y + mBondingBox.h)
		{
			mIsSelected = true;
			return true;
		}
		UnSelect();
		return false;
	}
	void Draw()
	{
		if (mIsSelected)
		{
			glPointSize(mSelectedSize);
			glBegin(GL_POINTS);
			glColor3f(0, 0, 0);
			glVertex2f(mPosition.x, mPosition.y);
			glEnd();
		}
		glPointSize(mPixelSize);
		glBegin(GL_POINTS);
		glColor3f(0, 0, 1);
		glVertex2f(mPosition.x, mPosition.y);
		glEnd();
		glBegin(GL_LINE_LOOP);

		glColor4f(1.0f, .5f, .5f, .5f);
		glVertex3f(mBondingBox.x, mBondingBox.y, 1);
		glVertex3f(mBondingBox.x + mBondingBox.w, mBondingBox.y, 1);
		glVertex3f(mBondingBox.x + mBondingBox.w, mBondingBox.y + mBondingBox.h, 1);
		glVertex3f(mBondingBox.x, mBondingBox.y + mBondingBox.h, 1);
		glEnd();
	}
	
	float GetX()
	{
		return mPosition.x;
	}
	float GetY()
	{
		return mPosition.y;
	}
	Vector2D GetVector2D()
	{
		return mPosition;
	}
};