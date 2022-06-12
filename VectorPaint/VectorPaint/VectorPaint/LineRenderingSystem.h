#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ECS.h"
#include "LineComponent.h"
#include "Manager.h"
#include "TransformComponent.h"

class LineRendererSystem : public ECS::System
{
public:
	LineComponent* mLineComponent;
	TransformComponent* transformComponent;
	Renderer* renderer;
	Model* model;
	~LineRendererSystem() override {}
	void Initialize() override
	{
		if (entity->hasComponent<LineComponent>())
		{
			mLineComponent = entity->getComponent<LineComponent>();
		}
		if (entity->hasComponent<TransformComponent>())
		{
			transformComponent = entity->getComponent<TransformComponent>();
		}
		renderer = Manager::GetInstance()->GetRenderer();
		model = mLineComponent->GetModel();
	}
	void Update() override
	{
		model->SetPosition(glm::vec2(transformComponent->Position.x, transformComponent->Position.y));
		model->SetScale(glm::vec2(transformComponent->Scale.x, transformComponent->Scale.y));
	}
	void Render() override
	{
		glBegin(GL_LINES);
		glm::vec4 modelColor = model->GetColor();
		glColor4f(modelColor.r, modelColor.g, modelColor.b, modelColor.a);
		glVertex3f(mLineComponent->mLineStart.x, mLineComponent->mLineStart.y, 1);
		glVertex3f(mLineComponent->mLineEnd.x, mLineComponent->mLineEnd.y, 1);
		glEnd();
	//	Rect viewPortRect = renderer->GetViewportRect();
	//	glm::vec2 viewPort = glm::vec2(viewPortRect.w, viewPortRect.h);
	//	renderer->shaders[(int)(ShaderType::LineShader)]->SetVec2f(glm::vec2(mLineComponent.mLineStart.x, mLineComponent.mLineStart.y),"line.start");
	//	renderer->shaders[(int)(ShaderType::LineShader)]->SetVec2f(glm::vec2(mLineComponent.mLineEnd.x, mLineComponent.mLineEnd.y),"line.end");
	//	renderer->shaders[(int)(ShaderType::LineShader)]->SetVec2f(glm::vec2(transformComponent.Scale.x, transformComponent.Scale.y),"line.scale");
	//	renderer->shaders[(int)(ShaderType::LineShader)]->SetVec2f(viewPort,"line.viewport");
	//	renderer->shaders[(int)(ShaderType::LineShader)]->Set1f(mLineComponent.mLineWidth,"line.thickness");
	//	model->render(renderer->shaders[(int)(ShaderType::LineShader)]);
	}
};