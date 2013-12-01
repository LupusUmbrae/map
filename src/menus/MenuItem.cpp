/*
 * MenuItem.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#include "MenuItem.h"
namespace menu {

MenuItem::MenuItem(std::string name, std::string tooltip, IMenuAction* action,
		utils::MapTexture* icon, utils::MapTexture* iconHover) {
	this->name = name;
	this->tooltip = tooltip;
	this->action = action;
	this->icon = icon;
	this->iconHover = iconHover;

}

MenuItem::~MenuItem() {
	// TODO Auto-generated destructor stub
}

utils::MapTexture* MenuItem::getIcon() {
	if (hover) {
		return iconHover;
	}

	return icon;
}

void MenuItem::setHover(bool hovering) {
	this->hover = hovering;
}

}