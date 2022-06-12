#include "ECSManager.h"
namespace ECS
{
	Entity& ECSManager::AddEntity()
	{
		Entity* e = new Entity();
		std::shared_ptr<Entity> sPtr{ e };
		entities.emplace_back(std::move(sPtr));
		return *e;
	}
	void ECSManager::Update()
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Update();
		}
	}
	void ECSManager::Render()
	{
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Render();
		}
	}
	void ECSManager::CleanUp()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::shared_ptr<Entity>& mEntity)
			{
				return !(mEntity->IsActive());
			}),
			std::end(entities));
	}
	void ECSManager::SelectEntity(std::vector<std::shared_ptr<ECS::Entity>> pEntities, Vector2D point)
	{
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