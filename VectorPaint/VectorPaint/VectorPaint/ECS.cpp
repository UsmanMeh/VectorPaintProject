#include "ECS.h"
#include "TransformComponent.h"
#include "PolygonComponent.h"
#include "ColliderComponent.h"
#include "PolygonRendererSystem.h"
namespace ECS
{
	void Entity::Update()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Update();
		}
		for (size_t i = 0; i < systems.size(); i++)
		{
			systems[i]->Update();
		}
	}
	void Entity::Render()
	{
		for (size_t i = 0; i < systems.size(); i++)
		{
			systems[i]->Render();
		}
	}
	bool Entity::Select(Vector2D pClickPoint)
	{
		return getComponent<ColliderComponent>()->CheckHit(pClickPoint);
	}
	bool Entity::IsActive() const
	{
		return active; 
	}
	bool Entity::ToBeDestroyed() const
	{
		return destroyed;
	}
	void Entity::SetActive(bool state)
	{
		active = state;
	}
	void Entity::Destroy()
	{
		destroyed = true;
	}
}