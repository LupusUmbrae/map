/*
 * TopMenu.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#ifndef TOPMENU_H_
#define TOPMENU_H_

#include <vector>

#include <SDL2/SDL.h>

#include "MenuItem.h"

class TopMenu {
public:
	TopMenu(int height, std::vector<MenuItem*> menuItems, SDL_Renderer* renderer);
	virtual ~TopMenu();

	void renderMenu(SDL_Renderer* renderer);


private:
	std::vector<MenuItem*> items;
	SDL_Texture* menuTexture = NULL;
	SDL_Rect* menuRectangle = new SDL_Rect;

};

#endif /* TOPMENU_H_ */
