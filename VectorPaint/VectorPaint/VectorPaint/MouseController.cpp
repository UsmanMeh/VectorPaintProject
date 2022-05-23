#include "MouseController.h"
#include "Rect.h"
#include "AddPolygonCommand.h"
#include "ToolsManager.h"
#include "Camera.h"
#include <algorithm>



//MouseController::MouseController(ECS::ECSManager* ecsMgr) : ecsManager(ecsMgr) {}
MouseController::~MouseController()
{
}

void MouseController::Initialize(Scene* pScene, Renderer* pRenderer)
{
	mToolsManager = ToolsManager::GetInstance();
	mRenderer = pRenderer;
	mScene = pScene;
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
			std::cout << "wheel.y" << event.wheel.y << std::endl;
			Camera::Zoom += static_cast<float>(event.wheel.y * 0.1f);
			Camera::Zoom = std::clamp(Camera::Zoom,0.1f,5.0f);
		if (event.wheel.y > 0)
		{
		}
		else if (event.wheel.y < 0)
		{
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "\n";
			SDL_GetMouseState(&startClick.first, &startClick.second);
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Left";
			MouseEvent(MouseState::down,MouseButton::left, Vector2D(static_cast<float>(startClick.first), static_cast<float>(startClick.second)));
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		else if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			MouseEvent(MouseState::down, MouseButton::middle, Vector2D(static_cast<float>(startClick.first), static_cast<float>(startClick.second)));
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
			MouseEvent(MouseState::up, MouseButton::left, Vector2D(static_cast<float>(endClick.first), static_cast<float>(endClick.second)));
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		else if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			MouseEvent(MouseState::up, MouseButton::middle, Vector2D(static_cast<float>(startClick.first), static_cast<float>(startClick.second)));
			std::cout << "Middle Mouse Button Pressed";
		}
		std::cout << " Click Up";
	}

	SDL_GetMouseState(&currentMousePos.first, &currentMousePos.second);
}

void MouseController::MouseEvent(MouseState ms ,MouseButton mb, Vector2D position)
{
	currentButton = mb;
	switch (mb)
	{
	case MouseButton::left:
		switch (ms)
		{
			case MouseState::down:
				start = position;
				OnLeftMouseDown(start);
				mouseDown = true;
				break;
			case MouseState::up:
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
			case MouseState::down:
				start = position;
				OnMiddleMouseDown(start);
				mouseDown = true;
				break;
			case MouseState::up:
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
Vector2D cameraStartingPos;
void MouseController::Update()
{
	switch (currentButton)
	{
	case MouseButton::left:
		break;
	case MouseButton::right:
		break;
	case MouseButton::middle:
		if (mouseDown)
		{
			//remap start Pos;
			Vector2D mousePos = Vector2D(static_cast<float>(currentMousePos.first), static_cast<float>(currentMousePos.second));
			Rect vRect = mRenderer->GetViewportRect();
			mousePos = reMap(mousePos, vRect);
			float cameraX = cameraStartingPos.x - (start.x - mousePos.x);
			float cameraY = cameraStartingPos.y - (start.y - mousePos.y);

			Camera::SetCameraPosition(cameraX, cameraY);

			std::cout << "Middle Mouse Down :: MouseX = " << start.x<< " MouseY = " << mousePos.x << "\n";
			std::cout << "Middle Mouse Down :: Camera::x = " << Camera::x << " Camera::y = " << Camera::y << "\n";
		}
		break;
	case MouseButton::none:
		break;
	default:
		break;
	}
}

void MouseController::Render()
{
	switch (currentButton)
	{
	case MouseButton::left:
		RenderDrawingRect();
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
void MouseController::RenderDrawingRect()
{
	Rect vRect = mRenderer->GetViewportRect();
	float mouseX = 0;
	float mouseY = 0;
	float startMouseX = 0;
	float startMouseY = 0;

	mouseX = (float)(currentMousePos.first - vRect.x) / (float)vRect.w;
	mouseY = (float)(currentMousePos.second - vRect.y) / (float)vRect.h;

	mouseX = map(currentMousePos.first, vRect.x, vRect.x + (float)vRect.w, -1, 1);
	mouseY = map(currentMousePos.second, vRect.y, vRect.y + (float)vRect.h, 1, -1);

	startMouseX = (float)(start.x - vRect.x) / (float)vRect.w;
	startMouseY = (float)(start.y - vRect.y) / (float)vRect.h;

	startMouseX = map(start.x, vRect.x, vRect.x + (float)vRect.w, -1, 1);
	startMouseY = map(start.y, vRect.y, vRect.y + (float)vRect.h, 1, -1);

	//std::cout << "currentMousePos = ("<< mouseX <<","<< mouseY <<")\n";
	if (mouseDown)
	{
		//Debug::LogToConsole(" startMouseX = "+ std::to_string(startMouseX) +"startMouseY = "+ std::to_string(startMouseY));
		//Debug::GetInstance()->Log(" Mouse X = "+ std::to_string(mouseX) +"Mouse Y = "+ std::to_string(mouseY));
		glLineWidth(3);
		glBegin(GL_LINE_LOOP);
		glColor4f(1.0f, .5f, .5f, .5f);
		glVertex3f(startMouseX, mouseY, 1);
		glVertex3f(mouseX, mouseY, 1);
		glVertex3f(mouseX, startMouseY, 1);
		glVertex3f(startMouseX, startMouseY, 1);
		glEnd();
		glFlush();
	}
}
bool IsInRange(Vector2D point)
{
	return point.x >= -1 && point.x <= 1 && point.y >= -1 && point.y < 1;
}
void MouseController::OnLeftMouseDown(Vector2D pos)
{
	std::cout << "OnMouseDownEvent\n";
}
void MouseController::OnLeftMouseUp(Vector2D startPos, Vector2D endPos)
{
	Rect vRect = mRenderer->GetViewportRect();
	//remap start Pos;
	startPos = reMap(startPos, vRect);
	//remap end Pos;
	endPos = reMap(endPos, vRect);
	ConvertToCameraSpace(&startPos);
	ConvertToCameraSpace(&endPos);
	Rect shapeRect(startPos.x, startPos.y, endPos.x, endPos.y);

	//if (IsInRange(startPos) || IsInRange(endPos))
	{
		std::unique_ptr<AddPolygonCommand>  addPolyCmd;
		switch (mToolsManager->GetSelectedTool())
		{
			case ToolsManager::Tools::Line:
			break;
			case ToolsManager::Tools::Rectangle:
			case ToolsManager::Tools::Square:
			case ToolsManager::Tools::Triangle:
				addPolyCmd = std::unique_ptr<AddPolygonCommand>(new AddPolygonCommand(mScene->mEntityManager, shapeRect));
				mScene ->mCommandManager->AddCommand(std::move(addPolyCmd));
				break;
			default:
			break;
		}
		//add shape
		Debug::LogToConsole("On Mouse Up Event (" + mToolsManager->ToolsNameList[mToolsManager->GetSelectedTool()] +")" );
		std::cout << "On Mouse Up Event\n";
	}
}
void MouseController::OnMiddleMouseDown(Vector2D pos)
{
	Rect vRect = mRenderer->GetViewportRect();
	start = reMap(start, vRect);
	cameraStartingPos = Vector2D(Camera::x, Camera::y);
}

void MouseController::OnMiddleMouseUp(Vector2D startPos, Vector2D endPos)
{
}

void MouseController::ConvertToCameraSpace(Vector2D* point)
{
	point->x -= Camera::x;
	point->y -= Camera::y;
	point->x /= Camera::Zoom;
	point->y /= Camera::Zoom;
}
