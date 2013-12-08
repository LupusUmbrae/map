/*
 * TileGroup.cpp
 *
 *  Created on: 8 Dec 2013
 *      Author: Robin
 */

#include "TileGroup.h"

namespace menu {

TileGroup::TileGroup(utils::MapTexture* groupName,
		std::vector<utils::MapTexture*> tiles) {
	this->groupName = groupName;
	this->tiles = tiles;
}

bool TileGroup::isOpen() {
	return this->open;
}

void TileGroup::setArea(int x, int y, int w, int h)
{
	areaRect->x = x;
	areaRect->y = y;
	areaRect->h = h;
	areaRect->w = w;
}

bool TileGroup::inArea(int x, int y) {
	if (x >= areaRect->x && (x <= (areaRect->x + areaRect->w))) {
		if (y >= areaRect->y && (y <= (areaRect->y + areaRect->h))) {
			return true;
		}
	}
	return false;
}

} /* namespace menu */
