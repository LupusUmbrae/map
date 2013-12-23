/*
 * MapTextures.cpp
 *
 *  Created on: 30 Nov 2013
 *      Author: Robin
 */

#include "MapTextures.h"

namespace utils
{

MapTexture::MapTexture()
{
	width = 0;
	height = 0;
}

MapTexture::~MapTexture()
{
	this->unload();
}

void MapTexture::unload()
{
	SDL_DestroyTexture(texture);
}

int MapTexture::getHeight()
{
	return this->height;
}

int MapTexture::getWidth()
{
	return this->width;
}

void MapTexture::setUniqueName(std::string uniqueName)
{
	this->uniqueName = uniqueName;
}

std::string* MapTexture::getUniqueName()
{
	return &this->uniqueName;
}

void MapTexture::render(int xPos, int yPos, int width, int height,
		SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad =
	{ xPos, yPos, this->width, this->height };

	if (width > 0)
	{
		renderQuad.w = width;
	}

	if (height > 0)
	{
		renderQuad.h = height;
	}

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

} /* namespace utils */
