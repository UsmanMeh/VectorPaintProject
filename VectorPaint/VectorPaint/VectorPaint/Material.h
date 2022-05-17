#pragma once

#include <glad/glad.h>
#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\type_ptr.hpp>

#include"Shader.h"

class Material
{
private:
	glm::vec4 color;
	GLint texture;

public:
	Material() 
	{
		this->color = glm::vec4(1,1,1,1);
		this->texture = 0;
	}
	Material(
		glm::vec4 pColor,
		GLint ptexture
	)
	{
		this->color = pColor;
		this->texture = ptexture;
	}
	Material(
		glm::vec4 pColor
	)
	{
		this->color = pColor;
		this->texture = 0;
	}
	void setColor(
		glm::vec4 pColor
	)
	{
		this->color = pColor;
	}
	~Material() {}

	void SendToShader(Shader& program)
	{
		program.SetVec4f(this->color, "material.color");
		program.Set1i(this->texture, "material.mainTexture");
	}
};