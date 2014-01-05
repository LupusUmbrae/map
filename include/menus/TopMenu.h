/*
 * TopMenu.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#ifndef TOPMENU_H_
#define TOPMENU_H_

// C++ Includes
#include <vector>
#include <map>

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Map Includes
#include "../MapConstants.h"
#include "../utils/logger.h"
#include "../utils/MapTextures.h"

#include "../actions/ActionQueue.h"

#include "MenuItem.h"
#include "../IDisplay.h"

namespace menu {
class TopMenu: public display::IDisplay {
public:
	//! Constructor
	/*!
	 *
	 * @param offsetX X offset for the display
	 * @param offsetY Y offset for the display
	 * @param height height of the display
	 * @param width width of the display
	 * @param menuItems Items to add to the menu
	 * @param renderer global renderer
	 */
	TopMenu(int offsetX, int offsetY, int height, int width,
			std::vector<MenuItem*> menuItems,
			SDL_Renderer* renderer);
	virtual ~TopMenu();

	//! Render the drawing area
	void render();

	//! Handle an SDL Event
	void handleEvents(SDL_Event event);

private:
	//! draw the items on the top menu
	/*!
	 * As the top menu display is fairly static this draws all the items (aka. sets their SDL_Rects)
	 */
	void drawItems();

	//! items to add
	std::vector<MenuItem*> items;
	//! items after being located
	std::map<SDL_Rect*, MenuItem*> itemMap;

	//! tooltip to be displayed (NULL means do not show any)
	utils::MapTexture* tooltip = NULL;

};
}
#endif /* TOPMENU_H_ */
