#pragma once

#include <iostream>
#include "Vector2D.h"
#include "Renderer.h"
#include <SDL.h>
#include "Scene.h"
#include <functional>
#include <iostream>
#include "ToolsManager.h"
#include "Input.h"

class MouseController
{
private:
	Renderer* mRenderer;
	Scene* mScene;
	ToolsManager* mToolsManager;
	std::pair <int, int > currentMousePos;
	Vector2D mCurrentMP;
	std::vector<std::function<void( ButtonState, MouseButton, Vector2D)>> mMouseEventCallback;
	//void RenderDrawingRect();
	void OnLeftMouseUp(Vector2D startPos, Vector2D endPos);
	void OnLeftMouseDown(Vector2D Pos);
	void OnMiddleMouseUp(Vector2D startPos, Vector2D endPos);
	void OnMiddleMouseDown(Vector2D Pos);
	void TrigerMouseEvent(ButtonState, MouseButton, Vector2D);
public:
	~MouseController();
	void Initialize(Scene* pScene,Renderer* pRenderer);
	void UpdateEvent(SDL_Event event);
	void Render(); 
	void Update();
	void MouseEvent(ButtonState ms, MouseButton mb, Vector2D position);
	void SubscribeToMouseEvent(std::function<void(ButtonState, MouseButton, Vector2D)>);
	float map(float value,float pBaseFrom, float pBaseTo,float pMapFrom, float pMapTo) const 
	{
		return pMapFrom + (pMapTo - pMapFrom) * ((value - pBaseFrom) / (pBaseTo - pBaseFrom));
	}
	Vector2D reMap(Vector2D pPos, Rect pViewPortRect)
	{
		float mouseX = map(pPos.x,
			pViewPortRect.x,
			pViewPortRect.x + (float)pViewPortRect.w,
			0,
			pViewPortRect.x
		);
		float mouseY = map(pPos.y,
			pViewPortRect.y,
			pViewPortRect.y + (float)pViewPortRect.h,
			pViewPortRect.y,
			0
		);
		return Vector2D(mouseX, mouseY);
	}
	Vector2D reMapAbs(Vector2D pPos)
	{
		Rect vRect = mRenderer->GetViewportRect(); 
		Vector2D outPos = pPos.Subtract(vRect.GetOffset());
		Camera::ConvertToCameraSpace(&outPos);
		return outPos;
	}
	//glViewport(mWindow->Width / 2 - viewPortWidth / 2, mWindow->Height / 2 - viewportHeight / 2, viewPortWidth, viewportHeight);
	int add(int a, int b)
	{
		return a + b;
	}
	Vector2D reMap(Vector2D pPos)
	{
		return reMap(pPos, mRenderer->GetViewportRect());
	}
};