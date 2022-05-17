#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "ECS.h"
#include "Model.h"
#include "ToolsManager.h"

class PolygonComponent : public ECS::Component
{
	Model* model;
public:
	Mesh* mesh;
	Material* material;
	Texture* texture;
	PolygonComponent() {};
	PolygonComponent(Mesh* pMesh)
	{
		mesh = pMesh;
		material = new Material();
		texture = new Texture("test.png", GL_TEXTURE_2D);
	}
	~PolygonComponent() override {}
	void Initialize() override
	{
		model = new Model(mesh, material , texture, ToolsManager::GetInstance()->GetCurrentColor());
	}
	Model* GetModel()
	{
		return model;
	}
	void Update() override
	{
	}
};