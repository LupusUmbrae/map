/*
 * changeTile.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#include "ActionTexture.h"

namespace action {

ActionTile::ActionTile(utils::MapTexture* texture) {
	this->action = CHANGE_TILE;
	this->texture = texture;
}

utils::MapTexture* ActionTile::getTexture() {
	return this->texture;
}

} /* namespace action */
