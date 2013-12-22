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

class changeTile: public action::IAction {
public:
	changeTile(utils::MapTexture* tile);

	utils::MapTexture* getTile();

private:
	utils::MapTexture* tile;
};

} /* namespace action */
#endif /* CHANGETILE_H_ */
