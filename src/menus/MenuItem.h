/*
 * MenuItem.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

// C++ Includes
#include <string>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../actions/IAction.h"
#include "../utils/MapTextures.h"

namespace menu {

class MenuItem {
public:
	MenuItem(std::string name, utils::MapTexture* tooltip, action::IAction* action,
			utils::MapTexture* icon, utils::MapTexture* iconHover);
	virtual ~MenuItem();
	utils::MapTexture* getIcon();
	void setHover(bool hovering);

	std::string name;
	utils::MapTexture* tooltip;
	action::IAction* action;

private:
	bool hover = false;

	utils::MapTexture* icon;
	utils::MapTexture* iconHover;
};

}

#endif /* MENUITEM_H_ */
