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
		void AddLine(Rect pRect);
		void AddSquare(Rect pRect);
		void AddRectangle(Rect pRect);
		void AddTriangle(Rect pRect);

		template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs);
		template<typename T> T& getComponent() const;
		template <typename T> bool hasComponent() const;

		template <typename T, typename... TArgs> T& addSystem(TArgs&&... mArgs);
		template<typename T> T& getSystem() const;
		template <typename T> bool hasSystem() const;

		bool IsActive() const;
		void Destroy();
	};
}