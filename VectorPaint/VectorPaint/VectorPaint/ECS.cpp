#include "ECS.h"
#include "TransformComponent.h"
#include "PolygonComponent.h"
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
	void Entity::add()
	{
		this->addComponent<TransformComponent>(0.0f,0.0f,32,32,1,1);
		this->addComponent<PolygonComponent>();
		this->addSystem<PolygonRendererSystem>();
	}
	template <typename T, typename... TArgs> T & Entity::addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->Initialize();
		return *c;
	}
	template<typename T> T & Entity::getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	template <typename T> bool Entity::hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}
	template <typename T, typename... TArgs> T & Entity::addSystem(TArgs&&... mArgs)
	{
		T* s(new T(std::forward<TArgs>(mArgs)...));
		s->entity = this;
		std::unique_ptr<System> uPtr{ s };
		systems.emplace_back(std::move(uPtr));

		systemArray[getSystemTypeID<T>()] = s;
		systemBitset[getSystemTypeID<T>()] = true;

		s->Initialize();
		return *s;
	}
	template<typename T> T & Entity::getSystem() const
	{
		auto ptr(systemArray[getSystemTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	template <typename T> bool Entity::hasSystem() const
	{
		return systemArray[getSystemTypeID<T>()];
	}

	bool Entity::IsActive() const
	{
		return active; 
	}
	void Entity::Destroy()
	{
		active = false; 
	}
}