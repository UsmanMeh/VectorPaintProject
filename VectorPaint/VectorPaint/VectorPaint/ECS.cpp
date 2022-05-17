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
	//Selection , Line, Square, Rectangle, Triangle, Circle , size
	Mesh* mesh;
	void Entity::AddLine(Rect pRect)
	{
		mesh = new Mesh(
			Square(),
			glm::vec3(0.f, 0.f, 0.f), 
			glm::vec3(0.5f),
			glm::vec3(0.0f,0.0f,0.f),
			glm::vec3(1.0f)
		);

		this->addComponent<TransformComponent>(pRect.x+ pRect.w/2, pRect.y + pRect.h/2,32,32, pRect.w, pRect.h);
		this->addComponent<PolygonComponent>(mesh);
		this->addSystem<PolygonRendererSystem>();
	}
	void Entity::AddSquare(Rect pRect)
	{
		mesh = new Mesh(
			Square(),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f),
			glm::vec3(0.0f, 0.0f, 0.f),
			glm::vec3(1.0f)
		);
		//TODO :: need to link the actual view port res here.
		float aspactRatio = (1024.0f / 680.0f);
		if (pRect.w <= pRect.h)
		{
			std::cout << " aspect ration " << (float)(1024.0f / 680.0f) << "\n";
			this->addComponent<TransformComponent>(pRect.x + pRect.w / 2, pRect.y + pRect.h / 2, 32, 32, pRect.w, pRect.w * aspactRatio);
		}
		else
			this->addComponent<TransformComponent>(pRect.x + pRect.w / 2, pRect.y + pRect.h / 2, 32, 32, pRect.h , pRect.h * aspactRatio);
		this->addComponent<PolygonComponent>(mesh);
		this->addSystem<PolygonRendererSystem>();
	}
	void Entity::AddRectangle(Rect pRect)
	{
		mesh = new Mesh(
			Square(),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f),
			glm::vec3(0.0f, 0.0f, 0.f),
			glm::vec3(1.0f)
		);

		this->addComponent<TransformComponent>(pRect.x + pRect.w / 2, pRect.y + pRect.h / 2, 32, 32, pRect.w, pRect.h);
		this->addComponent<PolygonComponent>(mesh);
		this->addSystem<PolygonRendererSystem>();
	}
	void Entity::AddTriangle(Rect pRect)
	{
		mesh = new Mesh(
			Triangle(),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f),
			glm::vec3(0.0f, 0.0f, 0.f),
			glm::vec3(1.0f)
		);

		this->addComponent<TransformComponent>(pRect.x + pRect.w / 2, pRect.y + pRect.h / 2, 32, 32, pRect.w, pRect.h);
		this->addComponent<PolygonComponent>(mesh);
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