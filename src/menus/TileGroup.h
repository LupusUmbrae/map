/*
 * TileGroup.h
 *
 *  Created on: 8 Dec 2013
 *      Author: Robin
 */

#ifndef TILEGROUP_H_
#define TILEGROUP_H_

// C++ Includes
#include <vector>

// SDL Includes

// Map Includes
#include "../utils/MapTextures.h"
#include "../utils/logger.h"
#include "../actions/changeTile.h"
#include "../actions/ActionQueue.h"

namespace menu {

class TileGroup {
public:
	TileGroup(utils::MapTexture* groupName, std::vector <utils::MapTexture*> tiles);

	bool inArea(int x, int y);
	void setArea(int x, int y, int w, int h);
	void setSpacing(int spacer, int nameSize, int iconSize);

	void handleEvent(int x, int y);

	bool isOpen();
	void setOpen(bool open) {this->open = open;};
	utils::MapTexture* getGroupName() {return groupName; };
	std::vector <utils::MapTexture*> getTiles() {return tiles; };


private:
	SDL_Rect *areaRect = new SDL_Rect();

	int spacer; // spacer used to space icons
	int nameSize;
	int iconSize;

	utils::MapTexture* groupName;
	std::vector <utils::MapTexture*> tiles;
	bool open = true;

};

} /* namespace menu */
#endif /* TILEGROUP_H_ */
