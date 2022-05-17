#include "MouseController.h"
#include "Rect.h"
#include "AddPolygonCommand.h"
#include "ToolsManager.h"



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
bool mouseDown = false;
void MouseController::UpdateEvent(SDL_Event event)
{
	/*if (ImGui::GetIO().WantCaptureMouse)
	{
		mouseDown = false;
		return;
	}*/
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "\n";
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Left";
			SDL_GetMouseState(&startClick.first, &startClick.second);
			MouseEvent(MouseState::down, Vector2D(static_cast<float>(startClick.first), static_cast<float>(startClick.second)));
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		std::cout << " Click DOWN";
	}
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		std::cout << "\n";
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Left";
			SDL_GetMouseState(&endClick.first, &endClick.second);
			MouseEvent(MouseState::up, Vector2D(static_cast<float>(endClick.first), static_cast<float>(endClick.second)));
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		std::cout << " Click Up";
	}
	//SDL_GetMouseState(&currentMousePos.first, &currentMousePos.second);
}
Vector2D start;
void MouseController::MouseEvent(MouseState ms, Vector2D position)
{
	switch (ms)
	{
	case MouseState::down:
		start = position;
		OnMouseDown(start);
		mouseDown = true;
		break;
	case MouseState::up:
		OnMouseUp(start, position);
		mouseDown = false;
		start.Zero();
		break;
	default:
		break;
	}
}
void MouseController::Render()
{
	Rect vRect = mRenderer->GetViewportRect();
	float mouseX = 0;
	float mouseY = 0;
	//std::cout << "currentMousePos = ("<< currentMousePos.first <<","<< currentMousePos.second<<")\n";

	mouseX = (float)(currentMousePos.first - vRect.x)/ (float)vRect.w;
	mouseY = (float)(currentMousePos.second - vRect.y)/ (float)vRect.h;

	mouseX = map(currentMousePos.first,
		vRect.x, 
		vRect.x + (float)vRect.w,
		-1,
		1
		);
	mouseY = map(currentMousePos.second, 
		vRect.y,
		vRect.y + (float)vRect.h,
		1,
		-1
	);

	//std::cout << "currentMousePos = ("<< mouseX <<","<< mouseY <<")\n";

	//if (mouseDown)
	//	rectangleRGBA(Manager::renderer, startClick.first, startClick.second, currentMousePos.first, currentMousePos.second, 0, 255, 0, 255);
	//if (mouseDown)
	//{
	//	Debug::GetInstance()->Log(" Mouse X = ");
	//	float w = start.x - mouseX;
	//	float h = start.y - mouseY;
	//	glBegin(GL_QUADS);
	//	glColor4f(0, 1, 0, 1);
	//	glVertex3f(start.x, start.y, 0);
	//	glVertex3f(start.x + w, start.y, 0);
	//	glVertex3f(start.x + w, start.y + h, 0);
	//	glVertex3f(start.x, start.y + h, 0);
	//	glEnd();
	//}
}
void MouseController::OnMouseDown(Vector2D pos)
{
	std::cout << "OnMouseDownEvent\n";
}
bool IsInRange(Vector2D point)
{
	return point.x >= -1 && point.x <= 1 && point.y >= -1 && point.y < 1;
}
void MouseController::OnMouseUp(Vector2D startPos, Vector2D endPos)
{
	Rect vRect = mRenderer->GetViewportRect();
	//remap start Pos;
	startPos = reMap(startPos, vRect);
	//remap end Pos;
	endPos = reMap(endPos, vRect);

	Rect shapeRect(startPos.x, startPos.y, endPos.x-startPos.x, endPos.y - startPos.y);

	if (IsInRange(startPos) || IsInRange(endPos))
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
		Debug::GetInstance()->Log("On Mouse Up Event (" + mToolsManager->ToolsNameList[mToolsManager->GetSelectedTool()] +")" );
		std::cout << "On Mouse Up Event\n";
	}
}
