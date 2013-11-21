/*
 * Tile.cpp
 *
 *  Created on: 16 Nov 2013
 *      Author: Robin
 */

#include "Tile.h"

Tile::Tile(SDL_Rect* location, SDL_Texture* texture) {
	this->location = location;
	this->texture = texture;

}

Tile::~Tile() {
	this->location = NULL;
	this->texture = NULL;
}
