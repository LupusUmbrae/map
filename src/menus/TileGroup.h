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
#include "../actions/IAction.h"
#include "../actions/ActionQueue.h"

namespace menu {

/**
 *Tile group, this is created by reading a JSON file and loading the images specified by it.
 *This class is used to display tilesets in menu::LeftMenu display
 */
class TileGroup {
public:
	//! constructor
	/*!
	 *
	 * @param groupName Name of the group to be displayed
	 * @param tiles The tiles in this group
	 */
	TileGroup(utils::MapTexture* groupName,
			std::vector<utils::MapTexture*> tiles);

	//! Used to check if the mouse is in this diplay area
	/*!
	 * Used to check if the mouse is currently hovering over this.
	 * Much like (akak identical) to the one from display::IDisplay.
	 * @param x current mouses x position over the window
	 * @param y current mouses y position over the window
	 * @return if the mouses x,y are within the bounds of this display
	 */
	bool inArea(int x, int y);
	//! Sets the area for this display
	/*!
	 * Sets the area for this display, this is used in inArea
	 * @param x x location on the screen
	 * @param y y location on the screen
	 * @param w Width of the display
	 * @param h Height of the display
	 */
	void setArea(int x, int y, int w, int h);

	//! Sets the spacing
	/*!
	 * Sets the spacing used when drawing this group
	 * @param spacer Space between images (x & y)
	 * @param nameSize Space between the group name and the firt icons (y)
	 * @param iconSize Size of each image
	 */
	void setSpacing(int spacer, int nameSize, int iconSize);

	//! Handle a left click
	/*!
	 *
	 * @param x X location of the click
	 * @param y Y location of the click
	 */
	void handleEvent(int x, int y);

	//! Is the group currently open?
	bool isOpen();

	//! Get the group name
	utils::MapTexture* getGroupName() {
		return groupName;
	}
	;

	//! get the tiles
	std::vector<utils::MapTexture*> getTiles() {
		return tiles;
	}
	;

private:
	//! Bounding box for the display
	SDL_Rect *areaRect = new SDL_Rect();

	//! action to be passed to the queue
	action::IAction action;

	//! Space between images (x & y)
	int spacer;
	//! Space between the group name and the firt icons (y)
	int nameSize;
	//! Size of each image
	int iconSize;

	//! Group name to be displayed
	utils::MapTexture* groupName;
	//! Tile images
	std::vector<utils::MapTexture*> tiles;
	//! Is the group open?
	bool open = true;

};

} /* namespace menu */
#endif /* TILEGROUP_H_ */
