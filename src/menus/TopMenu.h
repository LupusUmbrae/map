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

#include "MenuItem.h"
#include "../IDisplay.h"

namespace menu {
class TopMenu: public display::IDisplay {
public:
	TopMenu(int offsetX, int offsetY, int height, int width,
			std::vector<MenuItem*> menuItems, TTF_Font* font,
			SDL_Renderer* renderer);
	virtual ~TopMenu();

	void render();
	void handleEvents(SDL_Event event);

private:
	void drawItems();

	std::vector<MenuItem*> items;
	std::map<SDL_Rect*, MenuItem*> itemMap;

	SDL_Texture* tooltip = NULL;
	TTF_Font* font;
	SDL_Color textColor = { 0, 0, 0 };

};
}
#endif /* TOPMENU_H_ */
