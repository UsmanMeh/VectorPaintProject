#pragma once
#include "ICommand.h"
#include "ECSManager.h"
#include "Camera.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "CircleRenderingSystem.h"
class AddCircleCommand :
    public ICommand
{
private:
    Vector2D mLineStart;
    Vector2D mLineEnd;
    float mLineWidth;
    std::shared_ptr<ECS::Entity> mEntity;
public:
    AddCircleCommand(ECS::ECSManager* pEntityManager, Vector2D pLineStart, Vector2D pLineEnd, float pLineWidth) :ICommand(pEntityManager), mLineStart(pLineStart), mLineEnd(pLineEnd), mLineWidth(pLineWidth)
    {}
    void Execute() override
    {
        Rect shapeRect(mLineStart.x, mLineStart.y, mLineEnd.x, mLineEnd.y);
        float w = shapeRect.w - shapeRect.x;
        float h = shapeRect.h - shapeRect.y;
        float absW = abs(w);
        float absH = abs(h);
        float cX = shapeRect.x + w / 2;
        float cy = shapeRect.y + h / 2;

        mEntity = entityManager->AddEntity();
        mEntity->AddComponent<TransformComponent>(cX, cy, 32, 32, (w), (h));
        mEntity->AddComponent<CircleComponent>(mLineStart, mLineEnd, 5.0f);
        mEntity->addSystem<CircleRendererSystem>();

        if (absW <= absH)
        {
            mEntity->AddComponent<ColliderComponent>(cX - absW / 2, cy - (absW ) / 2, absW, absW );
            Debug::LogToConsole("Case A");
        }
        else
        {
            mEntity->AddComponent<ColliderComponent>(cX - (absH ) / 2, cy - absH / 2, absH , absH);
            Debug::LogToConsole("Case B");
        }
    }
    void Undo()  override
    {
        entityManager->SetEntityActiveState(mEntity,false);
    }
    void Redo()  override
    {
        entityManager->SetEntityActiveState(mEntity, true);
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
        return "Add Circle Command";
    }
    void Clean() override
    {
        entityManager->RemoveEntity(mEntity);
    }
};