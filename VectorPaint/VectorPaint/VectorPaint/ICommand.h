#pragma once
#include <memory>
#include <string>
#include "ECSManager.h"
struct ICommand
{
	ECS::ECSManager* entityManager;
	ICommand():entityManager(nullptr){};
	ICommand(ECS::ECSManager* pEntityManager):entityManager(pEntityManager){}
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual void Clean() = 0;
	virtual int Compair(std::shared_ptr<ICommand> pCommand) = 0;
	virtual void Merge(std::shared_ptr<ICommand> pCommand) = 0;
	virtual std::string Debug() = 0;
};