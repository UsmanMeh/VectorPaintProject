#pragma once
#include "ECS.h"
namespace ECS
{
	class ECSManager
	{
	private:
		std::vector<std::shared_ptr<Entity>> entities;
	public:
		std::shared_ptr<Entity> AddEntity();
		bool RemoveEntity(std::shared_ptr<Entity> e);
		bool SetEntityActiveState(std::shared_ptr<Entity> e, bool state);
		void Update();
		void Render();
		void CleanUp();
		void SelectEntity(std::vector<std::shared_ptr<ECS::Entity>>& pEntities , Vector2D point);
	};
}

