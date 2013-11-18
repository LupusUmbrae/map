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

	menuRectangle->x = 0;
	menuRectangle->y = 0;
	menuRectangle->h = height;
	menuRectangle->w = 480;

	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderDrawRect( renderer, menuRectangle );

}

TopMenu::~TopMenu() {
	// TODO Auto-generated destructor stub
}

void TopMenu::renderMenu(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	//SDL_RenderDrawRect( renderer, menuRectangle );
	SDL_RenderFillRect( renderer, menuRectangle );
}

