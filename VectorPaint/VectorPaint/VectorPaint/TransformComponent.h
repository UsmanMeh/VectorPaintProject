#pragma once
#include "ECS.h"
#include "Vector2D.h"

class TransformComponent : public ECS::Component
{
public:
	Vector2D Position;
	Vector2D Scale;
	int Height = 32;
	int Width = 32;

	~TransformComponent() override
	{
	}
	void Initialize() override
	{}
	void Update() override
	{}

	TransformComponent()
	{
		Position.Zero();
		Scale.One();
	}
	TransformComponent(float p_scX, float p_scY)
	{
		Position.Zero();
		Scale = Vector2D(p_scX, p_scY);
	}


	TransformComponent(float p_x, float p_y, int p_w, int p_h, float p_scX, float p_scY)
	{
		Position.x = p_x;
		Position.y = p_y;
		Height = p_h;
		Width = p_w;
		Scale = Vector2D(p_scX, p_scY);
	}
	TransformComponent(Vector2D pPos , Vector2D pScale)
	{
		Position = pPos;
		Height = 32;
		Width = 32;
		Scale = pScale;
	}
};