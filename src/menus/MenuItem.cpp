/*
 * MenuItem.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#include "MenuItem.h"
namespace menu {

MenuItem::MenuItem(std::string name, utils::MapTexture* tooltip,
		action::IAction* action, utils::MapTexture* icon,
		utils::MapTexture* iconHover) {
	this->name = name;
	this->tooltip = tooltip;
	this->action = action;
	this->icon = icon;
	this->iconHover = iconHover;

}

MenuItem::~MenuItem() {
	delete action;
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
