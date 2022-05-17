#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ECS.h"
#include "Components.h"
#include "Renderer.h"
#include "Manager.h"

class PolygonRendererSystem : public ECS::System
{
public:
	std::vector<GLfloat> rect_vertices;
	PolygonComponent polygonComponent;
	TransformComponent transformComponent;
	Renderer* renderer;
	Model* model;
	~PolygonRendererSystem() override{}
	void Initialize() override
	{
		if (entity->hasComponent<PolygonComponent>())
		{
			polygonComponent = entity->getComponent<PolygonComponent>();
		}
		if (entity->hasComponent<TransformComponent>())
		{
			transformComponent = entity->getComponent<TransformComponent>();
		}
		renderer = Manager::GetInstance()->GetRenderer();
		model = polygonComponent.GetModel();
	}
	void Update() override
	{
		//transformComponent.Position.x += .01;
		//if (transformComponent.Position.x > 1.5f)
		//	transformComponent.Position.x = -1.5f;
		model->SetPosition(glm::vec2(transformComponent.Position.x, transformComponent.Position.y));
		model->SetScale(glm::vec2(transformComponent.Scale.x, transformComponent.Scale.y));
	}
	void Render() override 
	{
		model->render(renderer->shader);
	}
};