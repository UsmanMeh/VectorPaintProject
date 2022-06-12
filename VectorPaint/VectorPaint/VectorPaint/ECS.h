#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <memory>
#include <algorithm>
#include "Vector2D.h"
#include "Rect.h"

namespace ECS
{
	constexpr std::size_t maxComponents = 32;
	constexpr std::size_t maxSystems = 32;
	constexpr std::size_t maxGroups = 32;
	class Component;
	class System;
	class Entity;
	inline  std::size_t getNewComponentTypeID()
	{
		static std::size_t lastComponentID = 0u;
		return lastComponentID++;
	}

	template <typename T> inline std::size_t getComponentTypeID() noexcept
	{
		static std::size_t typeID = getNewComponentTypeID();
		return typeID;
	}

	inline  std::size_t getNewSystemTypeID()
	{
		static std::size_t lastSystemID = 0u;
		return lastSystemID++;
	}

	template <typename T> inline std::size_t getSystemTypeID() noexcept
	{
		static std::size_t typeID = getNewSystemTypeID();
		return typeID;
	}

	class Component
	{
	public:
		Entity* entity;
		virtual void Initialize() {}
		virtual void Update() {}
		virtual ~Component() {}
	};

	class System
	{
	public:
		Entity* entity;
		virtual void Initialize() {}
		virtual void Update() {}
		virtual void Render() {}
		virtual ~System() {}
	};

	class Entity
	{
	private:
		bool active = true;
		bool destroyed = false;
		std::vector<std::unique_ptr<Component>> components;
		std::vector<std::unique_ptr<System>> systems;

		std::array<Component*, maxComponents> componentArray;
		std::array<System*, maxComponents> systemArray;

		std::bitset<maxComponents> componentBitset;
		std::bitset<maxSystems> systemBitset;

	public:
		void Update();
		void Render();
		bool Select(Vector2D pClickPoint);

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... mArgs)
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

		template<typename T> T* getComponent() const
		{
			auto ptr(componentArray[getComponentTypeID<T>()]);
			return static_cast<T*>(ptr);
		}

		template <typename T> bool hasComponent() const
		{
			return componentBitset[getComponentTypeID<T>()];
		}
		template <typename T, typename... TArgs> T& addSystem(TArgs&&... mArgs)
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
		template<typename T> T& getSystem() const
		{
			auto ptr(systemArray[getSystemTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

		template <typename T> bool hasSystem() const
		{
			return systemArray[getSystemTypeID<T>()];
		}

		bool IsActive() const;
		bool ToBeDestroyed() const;
		void SetActive(bool state);
		void Destroy();
	};

}