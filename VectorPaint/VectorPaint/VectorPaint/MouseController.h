#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Renderer.h"
#include <SDL.h>
#include "Scene.h"
#include "ToolsManager.h"


enum class MouseState : std::size_t
{
	down,
	up,
};
class MouseController
{
private:
	Renderer* mRenderer;
	Scene* mScene;
	ToolsManager* mToolsManager;
	std::pair <int, int > currentMousePos;
public:
	~MouseController();
	//TransformComponent* transform;
	void Initialize(Scene* pScene,Renderer* pRenderer);
	void UpdateEvent(SDL_Event event);
	void Render(); 
	void MouseEvent(MouseState ms, Vector2D position);
	void OnMouseUp(Vector2D startPos, Vector2D endPos);
	void OnMouseDown(Vector2D Pos);

	float map(float value,
		float pBaseFrom, float pBaseTo,
		float pMapFrom, float pMapTo) const {
		return pMapFrom + (pMapTo - pMapFrom) * ((value - pBaseFrom) / (pBaseTo - pBaseFrom));
	}
	Vector2D reMap(Vector2D pPos, Rect pViewPortRect)
	{
		float mouseX = map(pPos.x,
			pViewPortRect.x,
			pViewPortRect.x + (float)pViewPortRect.w,
			- 1,
			1
		);
		float mouseY = map(pPos.y,
			pViewPortRect.y,
			pViewPortRect.y + (float)pViewPortRect.h,
			1,
			- 1
		);
		return Vector2D(mouseX, mouseY);
	}

};