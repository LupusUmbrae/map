/*
 * LeftMenu.cpp
 *
 *  Created on: 24 Nov 2013
 *      Author: Robin
 */

#include "LeftMenu.h"

namespace menu {

LeftMenu::LeftMenu(int offsetX, int offsetY, int height, int width) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

}

void LeftMenu::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, areaRect);
}

void LeftMenu::handleEvents(SDL_Event event) {

}

} /* namespace menu */
