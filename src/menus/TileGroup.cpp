/*
 * TileGroup.cpp
 *
 *  Created on: 8 Dec 2013
 *      Author: Robin
 */

#include "menus/TileGroup.h"

namespace menu {

utils::MapTexture* TileGroup::groupOpen = NULL;
utils::MapTexture* TileGroup::groupClosed = NULL;

void TileGroup::setImages(utils::MapTexture* groupOpen,
		utils::MapTexture* groupClosed) {
	TileGroup::groupOpen = groupOpen;
	TileGroup::groupClosed = groupClosed;
}

TileGroup::TileGroup(utils::MapTexture* groupName,
		std::vector<utils::MapTexture*> tiles) {
	this->groupName = groupName;
	this->tiles = tiles;
}

void TileGroup::handleEvents(SDL_Event event) {

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {

			if (this->open) {
				SDL_Rect* tileRect;
				utils::MapTexture* tileTex;
				for (auto itemIter = tileMap.begin(); itemIter != tileMap.end();
						++itemIter) {

					tileRect = itemIter->first;
					tileTex = itemIter->second;

					if (curX >= tileRect->x
							&& (curX <= (tileRect->x + scale))) {
						if (curY >= tileRect->y
								&& (curY <= (tileRect->y + scale))) {
							action.setAction(action::CHANGE_TILE);
							action.setObject(tileTex);
							action::ActionQueue::getInstance().addAction(
									&action);
							break;
						}
					}
				}
			}

			if (curX >= nameRect->x && (curX <= (nameRect->x + 10))) {
				if (curY >= nameRect->y && (curY <= (nameRect->y + 10))) {
					this->open = !this->open;
					this->changed = true;
				}
			}
		}
	}
}

void TileGroup::render() {
	SDL_Rect* tileRect;
	utils::MapTexture* tileTex;

	if (open) {
		groupOpen->render(nameRect->x, nameRect->y, 10, 10);
	} else {
		groupClosed->render(nameRect->x, nameRect->y, 10, 10);
	}
	groupName->render(nameRect->x + 20, nameRect->y);

	if (open) {
		for (auto itemIter = tileMap.begin(); itemIter != tileMap.end();
				++itemIter) {
			tileRect = itemIter->first;
			tileTex = itemIter->second;

			tileTex->render(tileRect->x, tileRect->y, scale, scale);
		}
	}
}

int TileGroup::redraw(int x, int y, int w) {
	areaRect->x = x;
	areaRect->y = y;
	areaRect->w = w;

	draw();
	this->changed = false;
	return areaRect->h;
}

bool TileGroup::isOpen() {
	return this->open;
}

void TileGroup::draw() {
	int renX = this->areaRect->x;
	int renY = this->areaRect->y;

	int SPACER = 5;

	int startX;
	int startY;

	startX = renX;
	startY = renY;

	renX += 5;
	renY += 5;

	nameRect->x = renX;
	nameRect->y = renY;

	if (open) {
		tileMap.clear();

		renY += 15;

		SDL_Rect* tileRect;
		for (utils::MapTexture* curTex : tiles) {
			tileRect = new SDL_Rect();

			tileRect->x = renX;
			tileRect->y = renY;
			tileMap.insert(std::make_pair(tileRect, curTex));
			renX += scale + SPACER;

			if (renX >= (areaRect->w - (scale + SPACER))) {
				renX = this->areaRect->x + SPACER;
				renY += scale + SPACER;
			}
		}
		renY += scale;
	} else {
		renY += 10;
	}

	areaRect->x = startX;
	areaRect->y = startY;
	areaRect->w = this->areaRect->w;
	areaRect->h = renY - startY;
}

} /* namespace menu */
