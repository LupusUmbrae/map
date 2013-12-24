/*
 * changeTile.h
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#ifndef CHANGETILE_H_
#define CHANGETILE_H_

// C++ Includes
#include <iostream>

// SDL Includes

// Map Includes
#include "IAction.h"

#include "../utils/MapTextures.h"

namespace action {

class ActionTile: public action::IAction {
public:
	ActionTile(utils::MapTexture* texture);

	utils::MapTexture* getTexture();

private:
	utils::MapTexture* texture;
};

} /* namespace action */
#endif /* CHANGETILE_H_ */
