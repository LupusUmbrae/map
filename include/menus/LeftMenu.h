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

/**
 * This class creates a side menu of collapsable groups
 */
class LeftMenu: public display::IDisplay {
public:
	//! Create a left menu (well technically side menu)
	/*!
	 *
	 * @param offsetX X offset for the display
	 * @param offsetY Y offset for the display
	 * @param height height of the display
	 * @param width width of the display
	 * @param renderer global renderer
	 * @param groups All the tilesets
	 * @param groupClosed Group closed icon
	 * @param groupOpen Group open icon
	 */
	LeftMenu(int offsetX, int offsetY, int height, int width,
			SDL_Renderer* renderer, std::vector<TileGroup*> groups,
			utils::MapTexture* groupClosed, utils::MapTexture* groupOpen);

	//! Render the drawing area
	/*!
	 * Each time this is called is draws the items, not just render them
	 */
	void render();

	//! Handle an SDL Event
	void handleEvents(SDL_Event event);

private:

	//! Space between elements
	static const int SPACER = 5;

	//! Group close icon
	utils::MapTexture* groupClosed;
	//! Group open icon
	utils::MapTexture* groupOpen;
	//! Tilesets
	std::vector<TileGroup*> groups;
};

} /* namespace menu */
#endif /* LEFTMENU_H_ */
