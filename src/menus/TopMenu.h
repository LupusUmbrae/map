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
#include "../IDisplay.h"

class TopMenu : public display::IDisplay{
public:
	TopMenu(int height, std::vector<MenuItem*> menuItems, SDL_Renderer* renderer);
	virtual ~TopMenu();

	void render(SDL_Renderer* renderer);
	void handleEvents(SDL_Event event);


private:
	std::vector<MenuItem*> items;

};

#endif /* TOPMENU_H_ */
