/*
 * TopMenu.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#ifndef TOPMENU_H_
#define TOPMENU_H_

#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "MenuItem.h"
#include "../IDisplay.h"
namespace menu {
class TopMenu: public display::IDisplay {
public:
	TopMenu(int offsetX, int offsetY, int height, int width,
			std::vector<MenuItem*> menuItems, SDL_Renderer* renderer, TTF_Font* font);
	virtual ~TopMenu();

	void render(SDL_Renderer* renderer);
	void handleEvents(SDL_Event event);

private:
	void drawItems();

	SDL_Renderer* renderer;

	std::vector<MenuItem*> items;
	std::map<SDL_Rect*, MenuItem*> itemMap;

	TTF_Font* font;
		SDL_Texture* tooltip = NULL;
	SDL_Color textColor = { 0, 0, 0 };

};
}
#endif /* TOPMENU_H_ */
