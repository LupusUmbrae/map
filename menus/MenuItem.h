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

class MenuItem {
public:
	MenuItem();
	virtual ~MenuItem();
	std::string* name;
	std::string* tooltip;
	IMenuAction* action;

};

#endif /* MENUITEM_H_ */
