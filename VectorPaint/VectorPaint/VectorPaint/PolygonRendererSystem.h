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
	}
	void Update() override
	{
		float move = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5);

		float angle = 0;
		glm::vec3 axis_z(0, 0, 1);
		glm::mat4 m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(transformComponent.Position.x, transformComponent.Position.y, 0.0))
			*glm::scale(glm::mat4(1.0f), glm::vec3(transformComponent.Scale.x, transformComponent.Scale.y, 1));
		
		glUseProgram(renderer->program);
		glUniformMatrix4fv(renderer->uniform_m_transform, 1, GL_FALSE, glm::value_ptr(m_transform));
	}
	void Render() override 
	{
		GLfloat* vert_array = &polygonComponent.rect_vertices[0] ;
		glEnableVertexAttribArray(renderer->attribute_coord3d);
		glVertexAttribPointer(
			renderer->attribute_coord3d,   // attribute
			2,                   // number of elements per vertex, here (x,y,z)
			GL_FLOAT,            // the type of each element
			GL_FALSE,            // take our values as-is
			0,					 // next coord3d appears every 6 floats
			vert_array      // vertex array pointer
		);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(renderer->attribute_coord3d);
	}

};