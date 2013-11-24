/*
 * TopMenu.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#include "TopMenu.h"

namespace menu {

TopMenu::TopMenu(int offsetX, int offsetY, int height, int width,
		std::vector<menu::MenuItem*> menuItems, SDL_Renderer* renderer) {
	items = menuItems;

	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

	this->drawItems(renderer);
}

TopMenu::~TopMenu() {
	// TODO Auto-generated destructor stub
}

void TopMenu::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderDrawRect( renderer, menuRectangle );
	SDL_RenderFillRect(renderer, areaRect);

	// Draw the items
	SDL_Rect* curRect;
	menu::MenuItem* curItem;
	for (auto itemIter = itemMap.begin(); itemIter != itemMap.end();
			++itemIter) {

		curRect = itemIter->first;
		curItem = itemIter->second;
		SDL_RenderCopy(renderer, curItem->getIcon(), NULL, curRect);
	}
}

void TopMenu::handleEvents(SDL_Event event) {
	SDL_Rect* curRect;
	menu::MenuItem* curItem;
	bool found = false;
	;

	/**
	 * First find if the mouse is over something. Also reset all hovers
	 */
	for (auto itemIter = itemMap.begin(); itemIter != itemMap.end();
			++itemIter) {
		curRect = itemIter->first;

		if (curX >= curRect->x && (curX <= (curRect->x + curRect->h))) {
			if (curY >= curRect->y && (curY <= (curRect->y + curRect->w))) {
				found = true;
				curItem = itemIter->second;
			}
		}
		itemIter->second->setHover(false);
	}

	if (found) {
		if (event.type == SDL_MOUSEMOTION) {
			curItem->setHover(true);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {

		}
	}
}

void TopMenu::drawItems(SDL_Renderer* renderer) {
	int x = 2;
	int spacer = 5;

	for (menu::MenuItem* item : items) {
		SDL_Rect* dst = new SDL_Rect();
		dst->x = x;
		dst->y = 2;
		SDL_QueryTexture(item->getIcon(), NULL, NULL, &dst->w, &dst->h);

		itemMap.insert(std::make_pair(dst, item));

		x = dst->w + spacer;
	}
}

}
