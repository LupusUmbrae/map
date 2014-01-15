/*
 * LeftMenu.cpp
 *
 *  Created on: 24 Nov 2013
 *      Author: Robin
 */

#include "menus/LeftMenu.h"

namespace menu {

LeftMenu::LeftMenu(int offsetX, int offsetY, int height, int width,
		SDL_Renderer* renderer, std::vector<TileGroup*> groups,
		utils::MapTexture* groupClosed, utils::MapTexture* groupOpen) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

	this->groups = groups;

	this->renderer = renderer;

	draw();
}

void LeftMenu::render() {
	SDL_SetRenderDrawColor(renderer, 0xF0, 0xF0, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, areaRect);

	bool changed = false;
	int y = 0;
	for (TileGroup* curGroup : groups) {
		if (!changed) {
			changed = curGroup->hasChanged();

			if (changed) {
				y = curGroup->getArea().y;
				y += curGroup->redraw(areaRect->x, y, areaRect->w);
			}
			curGroup->render();
		} else {
			y += curGroup->redraw(areaRect->x, y, areaRect->w);
			curGroup->render();
		}
	}
}

void LeftMenu::handleEvents(SDL_Event event) {
	// Pass it into the correct tile group
	for (TileGroup* curGroup : groups) {
		if (curGroup->inArea(curX, curY)) {
			curGroup->handleEvents(event);
			break;
		}
	}
}

void LeftMenu::draw() {
	int y = areaRect->y;

	// Tell each tile group to re-draw itself
	for (TileGroup* curGroup : groups) {
		y += curGroup->redraw(areaRect->x, y, areaRect->w);
		y += SPACER;
	}
}

} /* namespace menu */
