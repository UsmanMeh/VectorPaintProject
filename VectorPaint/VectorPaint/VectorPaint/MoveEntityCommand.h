#pragma once
#include "ICommand.h"
#include "ECSManager.h"
#include "TransformComponent.h"
class MoveEntityCommand :
	public ICommand
{
private:
	std::shared_ptr<ECS::Entity> mEntity;
	Vector2D mTo;
	Vector2D mFrom;
	bool mEndCommand;
public:
	MoveEntityCommand(ECS::ECSManager* pEntityManager, std::shared_ptr<ECS::Entity> pEntity , Vector2D pTo , bool pEndCommand = false):ICommand(pEntityManager),mEntity(pEntity), mTo(pTo) , mEndCommand(pEndCommand)
	{
		mFrom = mEntity->getComponent<TransformComponent>()->Position;
	}
	void Execute() override
	{
		Move(mTo);
	}
	void Undo()  override
	{
		Move(mFrom);
	}
	void Redo()  override
	{
		Move(mTo);
	}
	void Clean() override
	{
		entityManager->RemoveEntity(mEntity);
	}
	void Move(Vector2D pTo)
	{
		mEntity->getComponent<TransformComponent>()->Position = pTo;
	}
	int Compair(std::shared_ptr<ICommand> pCommand)  override
	{
		std::shared_ptr <MoveEntityCommand> moveCmd;
		if (moveCmd = std::dynamic_pointer_cast<MoveEntityCommand>(pCommand))
		{
			return (this->Same(moveCmd) && !mEndCommand)?1:0;
		}
		return 0;
	}
	void Merge(std::shared_ptr<ICommand> pCommand) override
	{
		std::shared_ptr <MoveEntityCommand> moveCmd;
		if (moveCmd = std::dynamic_pointer_cast<MoveEntityCommand>(pCommand))
		{
			this->mTo = moveCmd->mTo;
			this->mEndCommand == moveCmd->mEndCommand;
			Execute();
		}
	}
	bool Same(std::shared_ptr <MoveEntityCommand> moveCmd)
	{
		if (this->mEntity == moveCmd->mEntity)
		{
			return true;
		}
			return false;
	}
	std::string Debug()
	{
		return "Move Entity Command::( From = "+  mFrom.ToString() +" To "+ mTo.ToString() +" )";
	}
};