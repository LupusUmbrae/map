/*
 * LeftMenu.h
 *
 *  Created on: 24 Nov 2013
 *      Author: Robin
 */

#ifndef LEFTMENU_H_
#define LEFTMENU_H_

#include <SDL2/SDL.h>

// Map Includes
#include "../MapConstants.h"
#include "../utils/logger.h"
#include "../IDisplay.h"

namespace menu {

class LeftMenu: public display::IDisplay {
public:
	LeftMenu(int offsetX, int offsetY, int height, int width,
			SDL_Renderer* renderer);
	void render();
	void handleEvents(SDL_Event event);
};

} /* namespace menu */
#endif /* LEFTMENU_H_ */
