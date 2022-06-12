#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "Model.h"
#include "ECS.h"

class LineComponent : public ECS::Component
{
	Model* model;
public:
	Mesh* mesh;
	Material* material;
	Texture* texture;

	Vector2D mLineStart;
	Vector2D mLineEnd;
	float mLineWidth;
	LineComponent() {}
	LineComponent(Vector2D pLineStart, Vector2D pLineEnd , float pLineWidth):mLineStart(pLineStart), mLineEnd(pLineEnd) , mLineWidth(pLineWidth)
	{
		Vertex vertices[] =
		{						
			glm::vec3(mLineStart.x, mLineStart.y, 0.f),		glm::vec2(1.f, 1.f),
			glm::vec3(mLineStart.x, mLineStart.y, 0.f),		glm::vec2(0.f, 0.f),
		};
		GLuint indices[] =
		{
			0, 1,
		};
		mesh = new Mesh(Square(),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.5f),
			glm::vec3(0.0f, 0.0f, 0.f),
			glm::vec3(1.0f));

		material = new Material();
		texture = new Texture("test.png", GL_TEXTURE_2D);
	}
	~LineComponent() override {}
	void Initialize() override
	{
		model = new Model(mesh, material, texture, ToolsManager::GetInstance()->GetCurrentColor());
	}
	Model* GetModel()
	{
		return model;
	}
	void Update() override
	{

	}
};