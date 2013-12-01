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

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


// Map Includes


namespace utils {

/**
 * Wrapper for sdl textures
 */
class MapTexture {
public:
	MapTexture();
	~MapTexture();


	void render( int xPos, int yPos, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	int getHeight();
	int getWidth();

	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	void unload();


protected:
	int width;
	int height;

	SDL_Renderer* renderer;
	SDL_Texture* texture = NULL;
	TTF_Font* font = NULL;

};

} /* namespace utils */
#endif /* MAPTEXTURES_H_ */
