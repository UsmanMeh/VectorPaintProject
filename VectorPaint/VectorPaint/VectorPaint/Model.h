#pragma once

#include "Mesh.h"

class Model
{
private:
	Mesh* mesh;
	Material* material;
	Texture* mainTecture;
	glm::vec4 color;

public:
	Model(
		Mesh* pMesh,
		Material* pMaterial,
		Texture* pMainTecture,
		glm::vec4 pColor
	)
	{
		mesh = pMesh;
		material = pMaterial;
		mainTecture = pMainTecture;
		color = pColor;
	}
	~Model()
	{}

	void SetPosition(glm::vec2 pos)
	{
		mesh->setPosition(glm::vec3(pos, 0));
	}
	void SetScale(glm::vec2 scale)
	{
		mesh->setScale(glm::vec3(scale, 0));
	}
	void render(Shader* shader)
	{
		//Update uniforms
		this->material->setColor(color);
		this->material->SendToShader(*shader);

		shader->use();
		this->mainTecture->bind(0);
		mesh->render(shader);
		
	}
};