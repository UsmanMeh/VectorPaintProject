#pragma once
#include "MouseController.h"
#include "Input.h"
class DrawingManager : public MouseInput , public KeyboardInput
{
public:
	void Initialize();
	void MouseEvent(ButtonState ms, MouseButton mb, Vector2D position) override;
	void KeyboardEvent(ButtonState pbuttonState, const Uint8* pKeyState)override;
	void Render();
	void Update();
private:
	Renderer* mRenderer;
	Scene* mScene;
	ToolsManager* mToolsManager;
	Vector2D mStartMP; // Mouse start position on mouse down
	Vector2D mCurrentMP; // Mouse current position
	MouseButton currentButton = MouseButton::none;
	bool mMouseDown = false;
	bool mDrawingPath = false;
	std::vector<Vector2D> PathPoints;
	void OnLeftMouseUp(Vector2D startPos, Vector2D endPos);
	void OnLeftMouseDown(Vector2D Pos);
	void RenderDrawingPreview();
	void DrawCircle(float cx, float cy, float r, int segments, bool isVerticle);
	Rect GetBBFromPoints(std::vector<Vector2D>* Points);
};

