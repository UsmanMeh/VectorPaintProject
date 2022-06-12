#include "ECSManager.h"
#include "Debug.h"
namespace ECS
{
	std::shared_ptr<Entity> ECSManager::AddEntity()
	{
		Entity* e = new Entity();
		std::shared_ptr<Entity> sPtr{ e };
		entities.emplace_back(sPtr);
		return sPtr;
	}
	bool ECSManager::SetEntityActiveState(std::shared_ptr<Entity> e , bool state)
	{
		e->SetActive(state);
		return false;
	}
	bool ECSManager::RemoveEntity(std::shared_ptr<Entity> e)
	{
		e->Destroy();
		return false;
	}
	void ECSManager::Update()
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->IsActive())
				entities[i]->Update();
		}
	}
	void ECSManager::Render()
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			if(entities[i]->IsActive())
				entities[i]->Render();
		}
	}
	void ECSManager::CleanUp()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::shared_ptr<Entity>& mEntity)
			{
				return (mEntity->ToBeDestroyed());
			}),
			std::end(entities));
	}
	void ECSManager::SelectEntity(std::vector<std::shared_ptr<ECS::Entity>>& pEntities, Vector2D point)
	{
		if (entities.empty())
			return;
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->Select(point))
			{
				pEntities.push_back(entities[i]);
				return;
			}
		}
	}
}