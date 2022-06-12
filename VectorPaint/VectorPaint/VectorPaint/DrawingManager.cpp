#include "DrawingManager.h"
#include "Manager.h"
#include "Rect.h"
#include <math.h>
#include "AddPolygonCommand.h"
#include "AddLineCommand.h"
#include "ToolsManager.h"
#include "Camera.h"
#include <algorithm>
#include "GizmoManager.h"
#include "AddCircleCommand.h"
#include "AddPathCommand.h"


void DrawingManager::Initialize()
{
	mRenderer = Manager::GetInstance()->GetRenderer();
	mScene = Manager::GetInstance()->GetSceneManager()->GetActvieScene();
	mToolsManager = ToolsManager::GetInstance();

	// Subscribe to Mouse events from Mouse Controller.
	Manager::GetInstance()->GetMouseController()->SubscribeToMouseEvent(std::bind(&DrawingManager::MouseEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	// Subscribe to Keyboard events from Keyboard Controller.
	Manager::GetInstance()->GetKeyboardController()->SubscribeToKeyBoardEvent(std::bind(&DrawingManager::KeyboardEvent, this, std::placeholders::_1, std::placeholders::_2));
}
void DrawingManager::MouseEvent(ButtonState ms, MouseButton mb, Vector2D position)
{
	currentButton = mb;
	switch (mb)
	{
	case MouseButton::left:
		switch (ms)
		{
		case ButtonState::down:
			//Debug::LogToConsole("DrawingManager :: Left Mouse Down" + position.ToString());
			mStartMP = position;
			OnLeftMouseDown(mStartMP);
			mMouseDown = true;
			break;
		case ButtonState::up:
			//Debug::LogToConsole("DrawingManager :: Left Mouse Up" + position.ToString());
			OnLeftMouseUp(mStartMP, position);
			mMouseDown = false;
			mStartMP.Zero();
			break;
		default:
			break;
		}
		break;
	case MouseButton::right:
		break;
	}
}
void DrawingManager::KeyboardEvent(ButtonState pButtonState, const Uint8* pKeyState)
{
	if (pButtonState == ButtonState::down)
	{
		if (pKeyState[SDL_SCANCODE_RETURN])
		{
			switch (mToolsManager->GetSelectedTool())
			{
			case ToolsManager::Tools::Path:
				if (PathPoints.size() > 2) // create command if there are path points min 3 are required to make a shape command.
				{
					Rect shapeRect = GetBBFromPoints(&PathPoints);
					mScene->mCommandManager->AddCommand((std::shared_ptr<AddPathCommand>(new AddPathCommand(mScene->mEntityManager, shapeRect, PathPoints))));
				}
				PathPoints.clear();
				break;
			default:
				break;
			}
		}
		if(pKeyState[SDL_SCANCODE_ESCAPE])
		{
			switch (mToolsManager->GetSelectedTool())
			{
			case ToolsManager::Tools::Path:
				PathPoints.clear(); // cancel path.
				break;
			default:
				break;
			}
		}
	}
}
void DrawingManager::Render()
{
	switch (currentButton)
	{
	case MouseButton::left:
		RenderDrawingPreview();
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
void DrawingManager::Update()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	mCurrentMP = Vector2D(x, y);
	mCurrentMP = mCurrentMP.Subtract(mRenderer->GetViewportRect().GetOffset());
	Camera::ConvertToCameraSpace(&mCurrentMP);
}
void DrawingManager::OnLeftMouseDown(Vector2D pos)
{
	//ConvertToCameraSpace(&pos);
	switch (mToolsManager->GetSelectedTool())
	{
	case ToolsManager::Tools::Selection:
		mScene->mSelectionManager->SelectEntity(pos);
		break;
	case ToolsManager::Tools::Path:
		PathPoints.push_back(pos);
		break;
	}
	//std::cout << "OnMouseDownEvent\n";
}
void DrawingManager::OnLeftMouseUp(Vector2D startPos, Vector2D endPos)
{
	Rect shapeRect(startPos.x, startPos.y, endPos.x, endPos.y);

		std::unique_ptr<AddLineCommand>  addLineCmd;
		std::unique_ptr<AddPolygonCommand>  addPolyCmd;
		std::unique_ptr<AddCircleCommand>  addCircleCmd;
		switch (mToolsManager->GetSelectedTool())
		{
		case ToolsManager::Tools::Selection:
			break;
		case ToolsManager::Tools::Line:
			mScene->mCommandManager->AddCommand(std::shared_ptr<AddLineCommand>(new AddLineCommand(mScene->mEntityManager, startPos, endPos, 5.0f)));
			break;
		case ToolsManager::Tools::Rectangle:
		case ToolsManager::Tools::Square:
		case ToolsManager::Tools::Triangle:
			mScene->mCommandManager->AddCommand(std::shared_ptr<AddPolygonCommand>(new AddPolygonCommand(mScene->mEntityManager, shapeRect)));
			break;
		case ToolsManager::Tools::Circle:
			mScene->mCommandManager->AddCommand(std::shared_ptr<AddCircleCommand>(new AddCircleCommand(mScene->mEntityManager, startPos, endPos, 5.0f)));
			break;
		case ToolsManager::Tools::Path:
			if (PathPoints.size() > 2) // create command if there are path points min 3 are required to make a shape command.
			{

			}
			break;
		default:
			break;
		}
		//add shape
		//Debug::LogToConsole("On Mouse Up Event (" + mToolsManager->ToolsNameList[mToolsManager->GetSelectedTool()] + ")");
	
}
void DrawingManager::RenderDrawingPreview()
{
	Rect vRect = mRenderer->GetViewportRect();
	float mouseX = mCurrentMP.x;
	float mouseY = mCurrentMP.y;
	float startMouseX = mStartMP.x;
	float startMouseY = mStartMP.y;
	Rect bb;
	if (mMouseDown || mToolsManager->GetSelectedTool() == ToolsManager::Tools::Path)
	{
		float w = mouseX - startMouseX;
		float h = mouseY - startMouseY;
		float absW = abs(w);
		float absH = abs(h);
		float cX = startMouseX + w / 2;
		float cy = startMouseY + h / 2;
		glLineWidth(3);
		switch (mToolsManager->GetSelectedTool())
		{
		case ToolsManager::Tools::Selection:
			break;
		case ToolsManager::Tools::Line:
			glBegin(GL_LINES);
			glColor4f(1.0f, .5f, .5f, .5f);
			glVertex3f(startMouseX, startMouseY, 1);
			glVertex3f(mouseX, mouseY, 1);
			glEnd();
			break;
		case ToolsManager::Tools::Rectangle:
		case ToolsManager::Tools::Square:
		case ToolsManager::Tools::Triangle:
			glBegin(GL_LINE_LOOP);
			glColor4f(1.0f, .5f, .5f, .5f);
			glVertex3f(startMouseX, mouseY, 1);
			glVertex3f(mouseX, mouseY, 1);
			glVertex3f(mouseX, startMouseY, 1);
			glVertex3f(startMouseX, startMouseY, 1);
			glEnd();
			break;
		case ToolsManager::Tools::Circle:
			glBegin(GL_LINE_LOOP);
			glColor4f(1.0f, .5f, .5f, .5f);
			glVertex3f(startMouseX, mouseY, 1);
			glVertex3f(mouseX, mouseY, 1);
			glVertex3f(mouseX, startMouseY, 1);
			glVertex3f(startMouseX, startMouseY, 1);
			glEnd();

			DrawCircle(cX, cy, absW <= absH ? absW / 2.0f : absH / 2.0f, 50, absW <= absH);

			break;
		case ToolsManager::Tools::Path:
			if (PathPoints.size() > 0)
			{
				glBegin(GL_LINE_LOOP);
				glColor4f(1.0f, .5f, .5f, .5f);
				for (auto point : PathPoints)
				{
					glVertex3f(point.x, point.y, 1);
				}
					glVertex3f(mouseX, mouseY, 1);

				glEnd();
			}
			glPointSize(5.0f);
			glBegin(GL_POINTS);
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			for (auto point : PathPoints)
			{
				glVertex3f(point.x, point.y, 1);
			}
			glEnd();
			break;
		default:
			break;
		}
		glFlush();
	}
}
void DrawingManager::DrawCircle(float cx, float cy, float r, int segments, bool isVerticle) {
	glColor4f(1.0f, .5f, .5f, .5f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);//get the current angle 
		float x = r * cosf(theta); //calculate the x component 
		float y = r * sinf(theta); //calculate the y component 
		if (isVerticle)
			glVertex2f(x + cx, y + cy);//output vertex 
		else
			glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}
Rect DrawingManager::GetBBFromPoints(std::vector<Vector2D>* points)
{
	float xMin = 5000.0f;
	float yMin = 5000.0f;
	float xMax = -1.0f;
	float yMax = -1.0f;
	for (size_t i = 0; i < points->size(); i++)
	{
		if (xMin > points->at(i).x)
			xMin = points->at(i).x;
		if (xMax < points->at(i).x)
			xMax = points->at(i).x;
		if (yMin > points->at(i).y)
			yMin = points->at(i).y;
		if (yMax < points->at(i).y)
			yMax = points->at(i).y;
	}
	return Rect(xMin, yMin, xMax - xMin, yMax - yMin);
}