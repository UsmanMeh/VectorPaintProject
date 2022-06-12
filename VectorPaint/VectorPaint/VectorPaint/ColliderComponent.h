#include "ECS.h"
#include "Debug.h"
#pragma once
class ColliderComponent : public ECS::Component
{
private:
	Rect mBondingBox;
public:
	ColliderComponent(){};
	ColliderComponent(Rect pBondingBox)
	{
		mBondingBox = pBondingBox;
	};
	ColliderComponent(float px, float py, float pw ,float ph)
	{
		mBondingBox = Rect(px,py,pw,ph);
	};
	~ColliderComponent() override {}
	void Initialize() override
	{
	}
	void Update() override
	{
	}
	bool CheckHit(Vector2D pPoint)
	{
		if (pPoint.x > mBondingBox.x && pPoint.x < mBondingBox.x + mBondingBox.w &&
			pPoint.y > mBondingBox.y && pPoint.y < mBondingBox.y + mBondingBox.h)
		{
			return true;
		}
		return false;
	}
	Rect GetBB()
	{
		return mBondingBox;
	}
};