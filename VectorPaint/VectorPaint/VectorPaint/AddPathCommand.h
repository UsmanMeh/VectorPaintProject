#pragma once
#include "ICommand.h"
#include "delaunator.hpp"
#include <array>
#include "ECSManager.h"
#include "Camera.h"
#include "TransformComponent.h"
#include "PolygonRendererSystem.h"
#include "ColliderComponent.h"
#include "Mesh.h"

class AddPathCommand :
    public ICommand
{
private:
	ECS::ECSManager* entityManager;
	std::shared_ptr<ECS::Entity> mEntity;
	std::vector<Vector2D> mPathPoints;
	Rect mRect;
	Mesh* mesh;
public:
	AddPathCommand(ECS::ECSManager* pEntityManager, Rect pRect , std::vector<Vector2D> pPathPoints) :mRect(pRect), mPathPoints(pPathPoints)
	{
		entityManager = pEntityManager;
	}
	void Execute() override
	{
		mEntity = (entityManager->AddEntity());
		AddPath(mEntity);
	}
	void Undo()  override
	{
		entityManager->SetEntityActiveState(mEntity, false);
	}
	void Redo()  override
	{
		entityManager->SetEntityActiveState(mEntity, true);
	}
	void Clean() override
	{
		entityManager->RemoveEntity(mEntity);
	}
	void AddPath(std::shared_ptr<ECS::Entity> e)
	{
		std::vector<double> coords;

		for (auto v: mPathPoints)
		{
			coords.push_back(v.x);
			coords.push_back(v.y);
		}
	  // https://en.wikipedia.org/wiki/Delaunay_triangulation using implementation from https://github.com/delfrrr/delaunator-cpp/tree/master/include 
		delaunator::Delaunator d(coords);

		std::vector<Vertex> vertices;
		for (Vector2D vec : mPathPoints)
		{
			vertices.push_back({ glm::vec3(vec.x, vec.y,0), TexCordInRect(&vec,&mRect) });
		}

		mesh = new Mesh(
			vertices, d.triangles,
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f),
			glm::vec3(0.0f, 0.0f, 0.f),
			glm::vec3(1.0f)
		);

		float w = mRect.w;
		float h = mRect.h;
		float absW = abs(w);
		float absH = abs(h);
		float cX = mRect.x + w / 2;
		float cy = mRect.y + h / 2;

		e->AddComponent<TransformComponent>(0, 0, absW, absH, 1, 1);
		e->AddComponent<ColliderComponent>(mRect);
		e->AddComponent<PolygonComponent>(mesh);
		e->addSystem<PolygonRendererSystem>();
	}
	glm::vec2 TexCordInRect(const Vector2D* point, const Rect* rect)
	{
		float x = abs((point->x - rect->x)/ (rect->w));
		float y = abs((point->y - rect->y)/ (rect->h));
 		return glm::vec2(x,y);
	}
	int Compair(std::shared_ptr<ICommand> pCommand)  override
	{
		return 0;
	}
	void Merge(std::shared_ptr<ICommand> pCommand) override
	{
	}
	std::string Debug()
	{
		return "Add Path Command";
	}
};