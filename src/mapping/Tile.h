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
#include "../utils/logger.h"

/**
 * Class to store information about a tile on the map
 */
class Tile {
public:

	//! Constructor
	Tile(int x, int y, utils::MapTexture* texture);
	virtual ~Tile();

	//! Tiles x location
	int x;
	//! Tiles y location
	int y;
	//! Tiles texture
	utils::MapTexture* texture = NULL;

};

#endif /* TILE_H_ */
