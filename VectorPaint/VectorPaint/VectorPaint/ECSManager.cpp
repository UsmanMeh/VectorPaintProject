#include "ECSManager.h"
namespace ECS
{
	Entity& ECSManager::AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
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
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !(mEntity->IsActive());
			}),
			std::end(entities));
	}
}