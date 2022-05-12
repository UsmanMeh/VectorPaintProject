#pragma once
#include "ICommand.h"
#include "Components.h"
#include "ECSManager.h"
class AddPolygonCommand :
    public ICommand
{
private:
    ECS::ECSManager* entityManager;
    Vector2D mPos, mScale;
public:
    AddPolygonCommand(ECS::ECSManager* pEntityManager , Vector2D pPos ,Vector2D pScale)
    {
        entityManager = pEntityManager;
        mPos = pPos;
        mScale = pScale;
    }
    void Execute() override
    {
        auto& shape(entityManager->AddEntity());
        shape.add();
        //shape.addComponent<TransformComponent>(mPos, mScale);
        //shape.addComponent<PolygonComponent>();
        //shape.addSystem<PolygonRendererSystem>();
    }
    void Undo()  override
    {
    };
};

