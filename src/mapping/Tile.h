/*
 * Tile.h
 *
 *  Created on: 16 Nov 2013
 *      Author: Robin
 */

#ifndef TILE_H_
#define TILE_H_

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../utils/MapTextures.h"


class Tile {
public:
	Tile(SDL_Rect* location, utils::MapTexture* texture);
	virtual ~Tile();

	SDL_Rect* location = NULL;
	utils::MapTexture* texture = NULL;

};

#endif /* TILE_H_ */
