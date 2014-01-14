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
#include <map>

// SDL Includes

// Map Includes
#include "MenuItem.h"
#include "../IDisplay.h"
#include "../utils/MapTextures.h"
#include "../utils/textures/Text.h"
#include "../utils/logger.h"
#include "../actions/IAction.h"
#include "../actions/ActionQueue.h"

namespace menu {

/**
 *Tile group, this is created by reading a JSON file and loading the images specified by it.
 *This class is used to display tilesets in menu::LeftMenu display
 */
class TileGroup: public display::IDisplay {
public:
	//! Set the static images for tile groups
	/*!
	 *
	 *
	 *@param groupOpen Icon to show that the group is open
	 *@param groupClosed Icon to show that the group is closed
	 */
	static void setImages(utils::MapTexture* groupOpen,
			utils::MapTexture* groupClosed);

	//! constructor
	/*!
	 *
	 * @param groupName Name of the group to be displayed
	 * @param tiles The tiles in this group
	 */
	TileGroup(utils::MapTexture* groupName, std::vector<MenuItem*> tiles,
			SDL_Renderer* renderer);

	void handleEvents(SDL_Event event);

	void render();

	//! Re-draw the group with the new location
	/*!
	 * Redraw the group and return it's height.
	 *
	 * @param x X position on the screen of this group
	 * @param y Y position of the screen of this group
	 * @param w Width that this group can use
	 * @return height of the groups
	 */
	int redraw(int x, int y, int w);

	void addGroup(std::vector<MenuItem*> newGroup, std::string category);

	bool hasChanged();

	//! Is the group currently open?
	bool isOpen();

	//! Get the group name
	utils::MapTexture* getGroupName() {
		return groupName;
	}

private:
	//! Group close icon
	static utils::MapTexture* groupClosed;
	//! Group open icon
	static utils::MapTexture* groupOpen;

	//! Draws the group.
	void draw();

	//! action to be passed to the queue
	action::IAction action;

	//! Size of the tiles
	int scale = 20;

	//! Group name to be displayed
	utils::MapTexture* groupName;

	//! Tile images
	std::vector<MenuItem*> tiles;

	std::vector<TileGroup*> subGroups;

	//! Tile images with location on screen
	std::map<SDL_Rect*, MenuItem*> tileMap;

	//! Location for the open/close icon and name
	SDL_Rect* nameRect = new SDL_Rect();

	//! Is the group open?
	bool open = true;

	//! Has the group changed?
	/*!
	 * If the group has changed then this and all subsequent groups need to be redrawn.
	 *
	 * Change tends to only be when a group is opened or closed, thus shifting the vertical
	 * positions of all subsequent groups
	 */
	bool changed = false;

};

} /* namespace menu */
#endif /* TILEGROUP_H_ */
