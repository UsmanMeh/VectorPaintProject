#include "Texture.h"
void Texture::LoadFile(std::string path)
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
	//SDL_Surface* newSurface = SDL_CreateRGBSurface(0, width, height, 24, 0xff000000, 0x00ff0000, 0x0000ff00, 0);

	auto format = SDL_PixelFormatEnum(surf->format->format);
	SDL_Surface* newSurface = SDL_ConvertSurfaceFormat(surf, SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA8888, 0);
	//SDL_BlitSurface(surf, 0, newSurface, 0);
	format = SDL_PixelFormatEnum(newSurface->format->format);

	glGenTextures(1, &this->id);
	glBindTexture(type, this->id);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	//GLTexture::_pixelFormatParams(mTexData.pixelFormat, internalFormat, lockFormat, lockType);
	//glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
	glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, newSurface->pixels);
	//glGenerateMipmap(type);

	glActiveTexture(0);
	glBindTexture(type, 0);
	SDL_FreeSurface(surf);
}