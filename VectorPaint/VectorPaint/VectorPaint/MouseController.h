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
enum class MouseButton : std::size_t
{
	left,
	right,
	middle,
	none
};
class MouseController
{
private:
	Renderer* mRenderer;
	Scene* mScene;
	ToolsManager* mToolsManager;
	std::pair <int, int > currentMousePos;
	void RenderDrawingRect();
	void OnLeftMouseUp(Vector2D startPos, Vector2D endPos);
	void OnLeftMouseDown(Vector2D Pos);
	void OnMiddleMouseUp(Vector2D startPos, Vector2D endPos);
	void OnMiddleMouseDown(Vector2D Pos);
	void ConvertToCameraSpace(Vector2D* point);

public:
	~MouseController();
	void Initialize(Scene* pScene,Renderer* pRenderer);
	void UpdateEvent(SDL_Event event);
	void Render(); 
	void Update();
	void MouseEvent(MouseState ms, MouseButton mb, Vector2D position);

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