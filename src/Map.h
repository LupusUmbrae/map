/*
 * Sdl.h
 *
 *  Created on: 10 Nov 2013
 *      Author: Robin
 */

#ifndef SDL_H_
#define SDL_H_

// C++ Includes
#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>

#include <dirent.h>

#include <json/json.h>

#include <sstream>

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Map Includes
#include "MapConstants.h"

#include "utils/logger.h"
#include "utils/MapTextures.h"
#include "utils/textures/Image.h"
#include "utils/textures/Text.h"

#include "actions/ActionQueue.h"
#include "actions/IAction.h"

#include "mapping/Tile.h"

#include "menus/TopMenu.h"
#include "menus/LeftMenu.h"
#include "menus/MenuItem.h"
#include "menus/TileGroup.h"
#include "menus/DialogBox.h"

#include "mapping/DrawingArea.h"

/*
 * Actual code
 */

// Screeeeeen
const int SCREEN_WIDTH = 648;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

class Map {
public:
	//! Constructor
	Map();
	virtual ~Map();

	//! Initialises SDL, and other LIBs. Also created the renderer for the main window.
	/*!
	 *
	 * @return True if successful
	 */
	bool init();

	//! Loads the tilesets from json, creates the menus and drawing area.
	/*!
	 *
	 * @return True if successful
	 */
	bool loadResources();

	//! This is the entry to the run loop for SDL
	void run();

	//! Called after SDL_Quit, attempts to unload all resources
	void cleanUp();

	//! Processes SDL Events.
	/*!
	 * This method either sends the event to the correct display::IDisplay, or processes them itself
	 * @param event The event to process
	 */
	void handleEvent(SDL_Event event);

	//! Process Map Actions
	/*!
	 * Processes actions by calling specific funtions
	 * @param action Action to be processes
	 */
	void handleAction(action::IAction action);

	//! Renders all the displayss
	void render();

private:
	int curX = 0, curY = 0;

	// me window
	SDL_Window *screen = NULL;
	SDL_Renderer *renderer = NULL;

	// tiles
	std::vector<Tile*> tiles;

	//Displays
	menu::TopMenu* topMenu = NULL;

	mapping::DrawingArea* drawingArea = NULL;

	std::vector<std::vector<display::IDisplay*>> displaysNew;
	TTF_Font* font;
	TTF_Font* font2;

	//! Adds a new display to be rendered
	/*!
	 *Adds a new display to the correct Z-Index (layer), if the layer doesnt already exist a new one is created for it
	 * @param display display::IDisplay to be added
	 * @param zIndex Z-Index, or layer to add it to. The higher the number the higher the layer (0 = background layer)
	 */
	void addToDisplay(display::IDisplay* display, unsigned int zIndex = 0);

	//! Removes a display from rendering
	/*!
	 * Seach the layers for the given display and remove it
	 * @param display display::IDisplay to be removed
	 */
	void removeDisplay(display::IDisplay* display);

};

#endif /* SDL_H_ */
