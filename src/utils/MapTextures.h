/*
 * MapTextures.h
 *
 *  Created on: 30 Nov 2013
 *      Author: Robin
 */

#ifndef MAPTEXTURES_H_
#define MAPTEXTURES_H_

// C++ Includes
#include <iostream>
#include <string>
#include <vector>

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Map Includes
#include "logger.h"

namespace utils {

/**
 * Wrapper for sdl textures
 */
class MapTexture {
public:
	MapTexture();
	~MapTexture();

	//! Static vector of all loaded textures. Texture MUST add themselves
	static std::vector<MapTexture*> loadedTextures;

	//! render this texture
	/*!
	 *
	 * @param xPos x position on the screen
	 * @param yPos y position on the screen
	 * @param width Scale to this width (Default is textures width)
	 * @param height Scale to this height (Default is textures height)
	 * @param clip Clip the image, only showing part (Default do not clip)
	 * @param angle Rotation of the image (Default 0)
	 * @param center A pointer to a point indicating the point around which the clipped texture will be rotated (Default NULL)
	 * @param flip An SDL_RendererFlip value stating which flipping actions should be performed on the texture (Default none)
	 */
	void render(int xPos, int yPos, int width = 0, int height = 0,
			SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

	//! Get the height of the texture
	int getHeight();
	//! Get the width of the texture
	int getWidth();

	//! get the textures unique name
	/*!
	 * The unique name is used when searching for an image, this is only really used for tilesets
	 * @return Unique name (this is normally <tilesetName>.<imageName> as defined in the JSON
	 */
	std::string* getUniqueName();

	//! sets the textures unique name
	/*!
	 * The unique name is used when searching for an image, this is only really used for tilesets
	 * @param uniqueName Unique name (this is normally <tilesetName>.<imageName> as defined in the JSON
	 */
	void setUniqueName(std::string uniqueName);

	//! Unload this texture (used for dynamic unloading)
	/*!
	 * Releases the texture and removes itself from the loadedTextures vector,
	 * this should be called instead of the deconstructor or deleting.
	 */
	void unload();

protected:

	//! Convert the surface created by a sub-implementation to a texture
	/*!
	 * Common surface conversion code for converting surfaces to textures
	 * @param surface surface to convert
	 * @return True if texture was created successfully
	 */
	bool convertSurface(SDL_Surface* surface);

	//! width of the texture
	int width;
	//! height of the texture
	int height;

	//! global renderer
	SDL_Renderer* renderer;
	//! The texture
	SDL_Texture* texture = NULL;

	//! the unique name
	std::string uniqueName;

};

} /* namespace utils */
#endif /* MAPTEXTURES_H_ */
