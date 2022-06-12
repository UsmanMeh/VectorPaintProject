#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ECS.h"
#include "Components.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "Manager.h"

class PolygonRendererSystem : public ECS::System
{
public:
	std::vector<GLfloat> rect_vertices;
	PolygonComponent* polygonComponent;
	TransformComponent* transformComponent;
	ColliderComponent* colliderComponent;
	Renderer* renderer;
	Model* model;
	Rect bb;
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
		if (entity->hasComponent<ColliderComponent>())
		{
			colliderComponent = entity->getComponent<ColliderComponent>();
		}
		
		bb = colliderComponent->GetBB();
		renderer = Manager::GetInstance()->GetRenderer();
		model = polygonComponent->GetModel();

	}
	void Update() override
	{
		//transformComponent.Position.x += .01;
		//if (transformComponent.Position.x > 1.5f)
		//	transformComponent.Position.x = -1.5f;
		model->SetPosition(glm::vec2(transformComponent->Position.x, transformComponent->Position.y));
		model->SetScale(glm::vec2(transformComponent->Scale.x, transformComponent->Scale.y));
	}
	void Render() override 
	{
		//glBegin(GL_LINE_LOOP);
		//glColor4f(1.0f, .5f, .5f, .5f);
		//glVertex3f(bb.x, bb.y, 1);
		//glVertex3f(bb.x + bb.w, bb.y, 1);
		//glVertex3f(bb.x + bb.w, bb.y + bb.h, 1);
		//glVertex3f(bb.x, bb.y + bb.h, 1);
		//glEnd();
		model->render(renderer->shaders[(int)(ShaderType::PlygonShader)]);
	}
};