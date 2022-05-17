#pragma once
#include "ICommand.h"
#include "Components.h"
#include "ECSManager.h"
class AddPolygonCommand :
    public ICommand
{
private:
    ECS::ECSManager* entityManager;
    Rect mRect;
    ToolsManager::Tools selectedTool;
public:
    AddPolygonCommand(ECS::ECSManager* pEntityManager , Rect pRect):mRect(pRect)
    {
        selectedTool = ToolsManager::GetInstance()->GetSelectedTool();
        entityManager = pEntityManager;
    }
    void Execute() override
    {
        auto& shape(entityManager->AddEntity());
        switch (selectedTool)
        {
        case ToolsManager::Square:
            shape.AddSquare(mRect);
            break;
        case ToolsManager::Rectangle:
            shape.AddRectangle(mRect);
            break;
        case ToolsManager::Triangle:
            shape.AddTriangle(mRect);
            break;

        default:
            break;
        }
    }
    void Undo()  override
    {
    };
};

