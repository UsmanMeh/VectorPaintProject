#pragma once
#include "ECS.h"
namespace ECS
{
	class ECSManager
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;
	public:
		Entity& AddEntity();
		void Update();
		void Render();
		void CleanUp();
	};
}

