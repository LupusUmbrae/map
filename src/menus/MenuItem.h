/*
 * MenuItem.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

#include <string>

#include <SDL2/SDL.h>

#include "IMenuAction.h"

namespace menu {

class MenuItem {
public:
	MenuItem(std::string name, std::string tooltip, IMenuAction* action,
			SDL_Texture* icon, SDL_Texture* iconHover);
	virtual ~MenuItem();
	SDL_Texture* getIcon();
	void setHover(bool hovering);

	std::string* name;
	std::string* tooltip;
	IMenuAction* action;

private:
	bool hover = false;

	SDL_Texture* icon;
	SDL_Texture* iconHover;
};

}

#endif /* MENUITEM_H_ */
