#include "MouseController.h"
#include "Rect.h"
#include <math.h>
#include "AddPolygonCommand.h"
#include "AddLineCommand.h"
#include "ToolsManager.h"
#include "Camera.h"
#include <algorithm>
#include "GizmoManager.h"
#include "AddCircleCommand.h"
#include "MoveEntityCommand.h"

//MouseController::MouseController(ECS::ECSManager* ecsMgr) : ecsManager(ecsMgr) {}
MouseController::~MouseController()
{
}

void MouseController::Initialize(Scene* pScene, Renderer* pRenderer)
{
	mRenderer = pRenderer;
	mScene = pScene;
	mToolsManager = ToolsManager::GetInstance();
}

std::pair <int, int > startClick;
std::pair <int, int > endClick;
Vector2D start;
bool mouseDown = false;
MouseButton currentButton = MouseButton::none;
void MouseController::UpdateEvent(SDL_Event event)
{
	if (ImGui::GetIO().WantCaptureMouse)
	{
		mouseDown = false;
		return;
	}
	if (event.type == SDL_MOUSEWHEEL)
	{
		Camera::SetCameraZoom(std::clamp(Camera::Zoom + static_cast<float>(event.wheel.y * 0.1f),1.0f,5.0f));
	}
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "\n";
			SDL_GetMouseState(&startClick.first, &startClick.second);
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Left";
			MouseEvent(ButtonState::down,MouseButton::left, Vector2D(static_cast<float>(startClick.first), static_cast<float>(startClick.second)));
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		else if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			MouseEvent(ButtonState::down, MouseButton::middle, Vector2D(static_cast<float>(startClick.first), static_cast<float>(startClick.second)));
			std::cout << "Middle Mouse Button Pressed";
		}
		std::cout << " Click DOWN";
	}
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		std::cout << "\n";
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Left";
			SDL_GetMouseState(&endClick.first, &endClick.second);
			MouseEvent(ButtonState::up, MouseButton::left, Vector2D(static_cast<float>(endClick.first), static_cast<float>(endClick.second)));
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		else if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			MouseEvent(ButtonState::up, MouseButton::middle, Vector2D(static_cast<float>(startClick.first), static_cast<float>(startClick.second)));
			std::cout << "Middle Mouse Button Pressed";
		}
		std::cout << " Click Up";
	}

	SDL_GetMouseState(&currentMousePos.first, &currentMousePos.second);
	mCurrentMP = Vector2D(currentMousePos.first, currentMousePos.second);
	mCurrentMP = mCurrentMP.Subtract(mRenderer->GetViewportRect().GetOffset());
	Camera::ConvertToCameraSpace(&mCurrentMP);
}

void MouseController::MouseEvent(ButtonState ms ,MouseButton mb, Vector2D position)
{
	currentButton = mb;
	position = reMapAbs(position);
	switch (mb)
	{
	case MouseButton::left:
	TrigerMouseEvent(ms, mb, position);
		switch (ms)
		{
			case ButtonState::down:
				start = position;
				OnLeftMouseDown(start);
				mouseDown = true;
				break;
			case ButtonState::up:
				OnLeftMouseUp(start, position);
				mouseDown = false;
				start.Zero();
				break;
			default:
				break;
		}
		break;
	case MouseButton::right:
		break;
	case MouseButton::middle:
		switch (ms)
		{
			case ButtonState::down:
				OnMiddleMouseDown(position);
				mouseDown = true;
				break;
			case ButtonState::up:
				mouseDown = false;
				start.Zero();
				break;
			default:
				break;
		}
		break;
	default:
		break;
	}
}
void MouseController::SubscribeToMouseEvent(std::function<void(ButtonState, MouseButton, Vector2D)> pCallback)
{
	mMouseEventCallback.push_back(pCallback);
}
Vector2D cameraStartingPos;
void MouseController::Update()
{
	switch (currentButton)
	{
	case MouseButton::left:
		if (mouseDown)
		{
			if (mScene->mSelectionManager->IsAnyEntitySelected())
			{
				mScene->mCommandManager->AddCommand((std::shared_ptr<MoveEntityCommand>(new MoveEntityCommand(mScene->mEntityManager,mScene->mSelectionManager->GetSelectedEntity(), mCurrentMP))));
			}
		}
		break;
	case MouseButton::right:
		break;
	case MouseButton::middle:
		if (mouseDown)
		{
			//remap start Pos;
			Vector2D mousePos = Vector2D(static_cast<float>(currentMousePos.first), static_cast<float>(currentMousePos.second));
			Rect vRect = mRenderer->GetViewportRect();
			mousePos = reMapAbs(mousePos);
			float cameraX = cameraStartingPos.x - (start.x - mousePos.x);
			float cameraY = cameraStartingPos.y - (start.y - mousePos.y);

			Camera::SetCameraPosition(cameraX, cameraY);
			
			//std::cout << "Middle Mouse Down :: MouseX = " << start.x<< " MouseY = " << mousePos.x << "\n";
			//std::cout << "Middle Mouse Down :: Camera::x = " << Camera::x << " Camera::y = " << Camera::y << "\n";
		}
		break;
	case MouseButton::none:
		break;
	default:
		break;
	}
	GizmoManager::GetInstance()->MousePositionUpdate(reMap(Vector2D(currentMousePos.first, currentMousePos.second)));
}

void MouseController::Render()
{
	switch (currentButton)
	{
	case MouseButton::left:
		break;
	case MouseButton::right:
		break;
	case MouseButton::middle:
		break;
	case MouseButton::none:
		break;
	default:
		break;
	}
}



bool IsInRange(Vector2D point)
{
	return point.x >= -1 && point.x <= 1 && point.y >= -1 && point.y < 1;
}
void MouseController::OnLeftMouseDown(Vector2D pos)
{
	//pos = reMap(pos);
	//Camera::ConvertToCameraSpace(&pos);
	GizmoManager::GetInstance()->OnMouseDown(true, pos);
	switch (mToolsManager->GetSelectedTool())
	{
		case ToolsManager::Tools::Selection:
			Debug::LogToConsole(pos.ToString());
			mScene->mSelectionManager->SelectEntity(pos);
			break;
	}
	std::cout << "OnMouseDownEvent\n";
}
void MouseController::OnLeftMouseUp(Vector2D startPos, Vector2D endPos)
{
	switch (currentButton)
	{
	case MouseButton::left:
		if (mScene->mSelectionManager->IsAnyEntitySelected())
		{
			mScene->mCommandManager->AddCommand((std::shared_ptr<MoveEntityCommand>(new MoveEntityCommand(mScene->mEntityManager,mScene->mSelectionManager->GetSelectedEntity(), mCurrentMP , true))));
		}
		break;
	}
}
void MouseController::OnMiddleMouseDown(Vector2D pos)
{
	Rect vRect = mRenderer->GetViewportRect();
	start = reMapAbs(pos);
	cameraStartingPos = Vector2D(Camera::x, Camera::y);
}

void MouseController::OnMiddleMouseUp(Vector2D startPos, Vector2D endPos)
{
}

void MouseController::TrigerMouseEvent(ButtonState ms, MouseButton mb, Vector2D position)
{
	for (auto& func : mMouseEventCallback)
	{
		func(ms, mb, position);
	}
}
