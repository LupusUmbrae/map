/*
 * Tile.h
 *
 *  Created on: 16 Nov 2013
 *      Author: Robin
 */

#ifndef TILE_H_
#define TILE_H_

#include <SDL2/SDL.h>



class Tile {
public:
	Tile(SDL_Rect* location, SDL_Texture* texture);
	virtual ~Tile();

	SDL_Rect* location = NULL;
	SDL_Texture* texture = NULL;

};

#endif /* TILE_H_ */
