#pragma once

#include<glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texcoord;
	void setPos(Vector2D pPos)
	{
		position = glm::vec3(pPos.x, pPos.y, 0);
	}
};