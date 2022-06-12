#pragma once
#include "ICommand.h"
#include "ECSManager.h"
#include "Camera.h"
#include "TransformComponent.h"
#include "PolygonRendererSystem.h"
#include "ColliderComponent.h"
#include "Mesh.h"
class AddPolygonCommand :
    public ICommand
{
private:
    std::shared_ptr<ECS::Entity> mEntity;
    Rect mRect;
	Mesh* mesh;
    ToolsManager::Tools selectedTool;
public:
    AddPolygonCommand(ECS::ECSManager* pEntityManager , Rect pRect):ICommand(pEntityManager),mRect(pRect)
    {
        selectedTool = ToolsManager::GetInstance()->GetSelectedTool();
    }
    void Execute() override
    {
        mEntity = (entityManager->AddEntity());
        switch (selectedTool)
        {
        case ToolsManager::Square:
            AddSquare(mEntity,mRect);
            break;
        case ToolsManager::Rectangle:
            AddRectangle(mEntity, mRect);
            break;
        case ToolsManager::Triangle:
           AddTriangle(mEntity, mRect);
            break;
        default:
            break;
        }
		entityManager->SetEntityActiveState(mEntity, true);
    }
	void Undo()  override
	{
		entityManager->SetEntityActiveState(mEntity, false);
	}
	void Redo()  override
	{
		entityManager->SetEntityActiveState(mEntity, true);
	}
	void Clean() override
	{
		entityManager->RemoveEntity(mEntity);
	}
	void AddSquare(std::shared_ptr<ECS::Entity> e, Rect pRect)
	{
		mesh = new Mesh(
			Square(),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f),
			glm::vec3(0.0f, 0.0f, 0.f),
			glm::vec3(1.0f)
		);

		float w = pRect.w - pRect.x;
		float h = pRect.h - pRect.y;
		float absW = abs(w);
		float absH = abs(h);
		float cX = pRect.x + w / 2;
		float cy = pRect.y + h / 2;

		if (absW <= absH)
		{
			e->AddComponent<TransformComponent>(cX, cy, absW, absW , w, w );
			e->AddComponent<ColliderComponent>(cX - absW / 2, cy - (absW ) / 2, absW, absW );
			Debug::LogToConsole("Case A");
		}
		else
		{
			e->AddComponent<TransformComponent>(cX, cy, absH, absH, h, h);
			e->AddComponent<ColliderComponent>(cX - (absH ) / 2, cy - absH / 2, absH , absH);
			Debug::LogToConsole("Case B");
		}
		e->AddComponent<PolygonComponent>(mesh);
		e->addSystem<PolygonRendererSystem>();
	}
	void AddRectangle(std::shared_ptr<ECS::Entity> e, Rect pRect)
	{
		mesh = new Mesh(
			Square(),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(1.0f)
		);
		float w = pRect.w - pRect.x;
		float h = pRect.h - pRect.y;
		float absW = abs(w);
		float absH = abs(h);
		float cX = pRect.x + w / 2;
		float cy = pRect.y + h / 2;

		Debug::LogToConsole(" Size on command side " + Vector2D(w,h).ToString());
		e->AddComponent<TransformComponent>(cX, cy, 32, 32, (w), (h));
		e->AddComponent<ColliderComponent>((cX)-absW / 2, (cy)-absH / 2, absW, absH);
		e->AddComponent<PolygonComponent>(mesh);
		e->addSystem<PolygonRendererSystem>();
	}
	void AddTriangle(std::shared_ptr<ECS::Entity> e, Rect pRect)
	{
		mesh = new Mesh(
			Triangle(),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f),
			glm::vec3(0.0f, 0.0f, 0.f),
			glm::vec3(1.0f)
		);

		float w = pRect.w - pRect.x;
		float h = pRect.h - pRect.y;
		float absW = abs(w);
		float absH = abs(h);
		float cX = pRect.x + w / 2;
		float cy = pRect.y + h / 2;

		e->AddComponent<TransformComponent>(cX, cy, 32, 32, (w), (h));
		e->AddComponent<ColliderComponent>((cX)-absW / 2, (cy)-absH / 2, absW, absH);

		e->AddComponent<PolygonComponent>(mesh);
		e->addSystem<PolygonRendererSystem>();
	}
	int Compair(std::shared_ptr<ICommand> pCommand)  override
	{
		return 0;
	}
	void Merge(std::shared_ptr<ICommand> pCommand) override
	{
	}
	std::string Debug()
	{
		return "Add Polygon Command";
	}
};

