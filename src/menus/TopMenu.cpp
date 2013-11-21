/*
 * TopMenu.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#include "TopMenu.h"

TopMenu::TopMenu(int height, std::vector<MenuItem*> menuItems,
		SDL_Renderer* renderer) {
	items = menuItems;

	areaRect->x = 0;
	areaRect->y = 0;
	areaRect->h = height;
	areaRect->w = 480;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, areaRect);

}

TopMenu::~TopMenu() {
	// TODO Auto-generated destructor stub
}

void TopMenu::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderDrawRect( renderer, menuRectangle );
	SDL_RenderFillRect(renderer, areaRect);
}

void TopMenu::handleEvents(SDL_Event event) {

}

