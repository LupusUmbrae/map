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

void TileGroup::setArea(int x, int y, int w, int h) {
	areaRect->x = x;
	areaRect->y = y;
	areaRect->h = h;
	areaRect->w = w;
}

void TileGroup::setSpacing(int spacer, int nameSize, int iconSize) {
	this->spacer = spacer;
	this->nameSize = nameSize;
	this->iconSize = iconSize;
}

bool TileGroup::inArea(int x, int y) {
	if (x >= areaRect->x && (x <= (areaRect->x + areaRect->w))) {
		if (y >= areaRect->y && (y <= (areaRect->y + areaRect->h))) {
			return true;
		}
	}
	return false;
}

void TileGroup::handleEvent(int x, int y) {

	if (this->open) {
		// Lets work out which icon
		int curX = areaRect->x;
		int curY = areaRect->y + nameSize;

		for (size_t i = 0; i < tiles.size(); i++) {
			if (x >= curX && (x <= (curX + iconSize))) {
				if (y >= curY && (y <= (curY + iconSize))) {
					action::ActionQueue::getInstance().addAction(new action::ActionTile(tiles.at(i)));
					break;
				}
			}
			curX += iconSize + spacer;
			if (curX >= (areaRect->w - (iconSize + spacer))) {
				curX = this->areaRect->x;
				curY += iconSize + spacer;
			}
		}
	}

	if (x >= areaRect->x && (x <= (areaRect->x + nameSize))) {
		if (y >= areaRect->y && (y <= (areaRect->y + nameSize))) {
			this->open = !this->open;
		}
	}
}

} /* namespace menu */
