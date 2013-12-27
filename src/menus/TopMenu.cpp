/*
 * TopMenu.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#include "TopMenu.h"

namespace menu {

TopMenu::TopMenu(int offsetX, int offsetY, int height, int width,
		std::vector<menu::MenuItem*> menuItems, TTF_Font* font,
		SDL_Renderer* renderer) {
	items = menuItems;

	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

	this->font = font;
	this->renderer = renderer;
	this->drawItems();
}

TopMenu::~TopMenu() {
	// TODO Auto-generated destructor stub
}

void TopMenu::render() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderDrawRect( renderer, menuRectangle );
	SDL_RenderFillRect(renderer, areaRect);

	// Draw the items
	SDL_Rect* curRect = NULL;
	menu::MenuItem* curItem;
	for (auto itemIter = itemMap.begin(); itemIter != itemMap.end();
			++itemIter) {

		curRect = itemIter->first;
		curItem = itemIter->second;
		curItem->getIcon()->render(curRect->x, curRect->y);
	}

	if (tooltip != NULL) {
		tooltip->render(curX + 10, curY);
	}

}

void TopMenu::handleEvents(SDL_Event event) {
	SDL_Rect* curRect;
	menu::MenuItem* curItem;
	bool found = false;

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
			tooltip = curItem->tooltip;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			action::ActionQueue::getInstance().addAction(&curItem->action);
		}
	} else {
		tooltip = NULL;
	}
}

void TopMenu::drawItems() {
	int x = 2;
	int spacer = 5;

	for (menu::MenuItem* item : items) {
		SDL_Rect* dst = new SDL_Rect();
		dst->x = x;
		dst->y = 2;
		dst->w = item->getIcon()->getWidth();
		dst->h = item->getIcon()->getHeight();

		itemMap.insert(std::make_pair(dst, item));

		x += dst->w + spacer;
	}
}

}
