/*
 * Tile.cpp
 *
 *  Created on: 16 Nov 2013
 *      Author: Robin
 */

#include "Tile.h"

Tile::Tile(SDL_Rect* location, utils::MapTexture* texture) {
	this->location = location;
	this->texture = texture;

}

Tile::~Tile() {
	delete location;
}
