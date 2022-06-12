#pragma once

#include<iostream>
#include<string>
#include "imgui.h"
#include <glad/glad.h>
#include <SDL_surface.h>
#include <SDL_image.h>


class Texture
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int type;

public:

	Texture(std::string path, GLenum type)
	{
		this->type = type;
		LoadFile(path);
	}

	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	GLuint GetID() const { return this->id; }
	void* GetImTextureID() const { return (void*)(intptr_t)this->id; }
	ImVec2 GetSize() const { return ImVec2(width , height); }

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->type, this->id);
	}

	void Unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	void LoadFile(std::string path);
};