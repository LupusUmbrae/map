/*
 * LeftMenu.cpp
 *
 *  Created on: 24 Nov 2013
 *      Author: Robin
 */

#include "LeftMenu.h"

namespace menu {

LeftMenu::LeftMenu(int offsetX, int offsetY, int height, int width,
		SDL_Renderer* renderer, std::vector<TileGroup*> groups,
		utils::MapTexture* groupClosed, utils::MapTexture* groupOpen) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

	this->groups = groups;
	this->groupClosed = groupClosed;
	this->groupOpen = groupOpen;

	this->renderer = renderer;
}

void LeftMenu::render() {
	SDL_SetRenderDrawColor(renderer, 0xF0, 0xF0, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, areaRect);

	int renX = this->areaRect->x;
	int renY = this->areaRect->y;

	int startX;
	int startY;

	for (TileGroup* curGroup : groups) {
		renX += SPACER;
		renY += SPACER;
		startX = renX;
		startY = renY;

		if (curGroup->isOpen()) {
			this->groupOpen->render(renX, renY, 10, 10);
			renX += 15;
			curGroup->getGroupName()->render(renX, renY);
			renX = this->areaRect->x + SPACER;
			renY += 15;
			for (utils::MapTexture* curTex : curGroup->getTiles()) {
				curTex->render(renX, renY, 20, 20);
				renX += 20 + SPACER;

				if (renX >= (areaRect->w - (20 + SPACER))) {
					renX = this->areaRect->x + SPACER;
					renY += 20 + SPACER;
				}

			}
			renY += 20;

		} else {
			this->groupClosed->render(renX, renY, 10, 10);
			renX += 10;
			curGroup->getGroupName()->render(renX, renY);
			renY += 10;
		}

		curGroup->setArea(startX, startY, this->areaRect->w, renY - startY);
		curGroup->setSpacing(SPACER, 10, 20);

		// prepare for the next item
		renX = this->areaRect->x;
		renY += SPACER;
	}
}

void LeftMenu::handleEvents(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			for (TileGroup* curGroup : groups) {
				if (curGroup->inArea(curX, curY)) {
					// icon or expand bit?
					curGroup->handleEvent(curX, curY);
					break;
				}
			}
		}
	}
}

} /* namespace menu */
