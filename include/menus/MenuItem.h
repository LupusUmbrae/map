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

/**
 * This class wraps menu items to allow tooltips, hover and actions to be stored
 */
class MenuItem {
public:
	//! Constructor
	/*!
	 *
	 * @param name Name of the item (not used..)
	 * @param tooltip Tooltip for this item
	 * @param action Action to be used if item is clicked
	 * @param icon Base image for the item
	 * @param iconHover image for this item when the mouse is hovering over it
	 */
	MenuItem(std::string name, utils::MapTexture* tooltip,
			action::IAction action, utils::MapTexture* icon,
			utils::MapTexture* iconHover);
	virtual ~MenuItem();

	//! Get the icon (if hovers set returns the hover image)
	utils::MapTexture* getIcon();
	//! Set whether the mouse is hovering over this item
	void setHover(bool hovering);

	//! Name of the item
	std::string name;
	//! Tooltip of the item
	utils::MapTexture* tooltip;
	//! items action
	action::IAction action;

private:
	//! currently being hovered over?
	bool hover = false;

	utils::MapTexture* icon;
	utils::MapTexture* iconHover;
};

}

#endif /* MENUITEM_H_ */
