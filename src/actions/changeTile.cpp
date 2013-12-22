/*
 * changeTile.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#include "changeTile.h"

namespace action {

changeTile::changeTile(utils::MapTexture* tile) {
	this->action = CHANGE_TILE;
	this->tile = tile;
}

utils::MapTexture* changeTile::getTile() {
	return this->tile;
}

} /* namespace action */
