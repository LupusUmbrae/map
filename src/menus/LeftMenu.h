/*
 * LeftMenu.h
 *
 *  Created on: 24 Nov 2013
 *      Author: Robin
 */

#ifndef LEFTMENU_H_
#define LEFTMENU_H_

// C++ Includes
#include <sstream>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../MapConstants.h"
#include "../utils/logger.h"
#include "../IDisplay.h"
#include "TileGroup.h"

namespace menu {

class LeftMenu: public display::IDisplay {
public:
	LeftMenu(int offsetX, int offsetY, int height, int width,
			SDL_Renderer* renderer, std::vector<TileGroup*> groups,
			utils::MapTexture* groupClosed, utils::MapTexture* groupOpen);
	void render();
	void handleEvents(SDL_Event event);

private:

	static const int SPACER = 5; // space between elements

	utils::MapTexture* groupClosed;
	utils::MapTexture* groupOpen;

	std::vector<TileGroup*> groups;
};

} /* namespace menu */
#endif /* LEFTMENU_H_ */
