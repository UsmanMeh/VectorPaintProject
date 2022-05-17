#pragma once

#include<iostream>
#include<string>
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
		loadFile(path);
	}

	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	inline GLuint getID() const { return this->id; }

	void bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(this->type, this->id);
	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	void loadFile(std::string path)
	{
		if (this->id)
		{
			glDeleteTextures(1, &this->id);
		}

		//Load the image from the file into SDL's surface representation
		SDL_Surface* surf = IMG_Load(path.c_str());
		//SDL_Surface* surf = SDL_LoadBMP("texture.bmp");

		if (surf == NULL)
		{
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED: " << path << "\nError = " << IMG_GetError() << "\n";
			return;
		}

		width = surf->w;
		height = surf->h;

		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
		glGenerateMipmap(type);


		glActiveTexture(0);
		glBindTexture(type, 0);
		SDL_FreeSurface(surf);
	}
};