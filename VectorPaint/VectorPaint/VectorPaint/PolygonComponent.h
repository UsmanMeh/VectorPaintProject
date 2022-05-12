#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "ECS.h"

class PolygonComponent : public ECS::Component
{
public:
	std::vector<GLfloat> rect_vertices;
	~PolygonComponent() override {}
	void Initialize() override
	{
		float size = 0.4f;
		rect_vertices.push_back(-1.0 * size);
		rect_vertices.push_back(-1.0 * size);
		rect_vertices.push_back(-1.0 * size);
		rect_vertices.push_back(1.0 * size);
		rect_vertices.push_back(1.0 * size);
		rect_vertices.push_back(1.0 * size);
		rect_vertices.push_back(-1.0 * size);
		rect_vertices.push_back(-1.0 * size);
		rect_vertices.push_back(1.0 * size);
		rect_vertices.push_back(1.0 * size);
		rect_vertices.push_back(1.0 * size);
		rect_vertices.push_back(-1.0 * size);
	}
	void Update() override
	{}
};