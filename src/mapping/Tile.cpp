/*
 * Tile.cpp
 *
 *  Created on: 16 Nov 2013
 *      Author: Robin
 */

#include "Tile.h"

Tile::Tile(int x, int y, utils::MapTexture* texture) {
	this->x = x;
	this->y = y;
	this->texture = texture;

}

Tile::~Tile() {

}
