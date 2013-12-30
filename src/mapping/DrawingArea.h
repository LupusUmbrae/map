/*
 * DrawingArea.h
 *
 *  Created on: 18 Nov 2013
 *      Author: Robin
 */

#ifndef DRAWINGAREA_H_
#define DRAWINGAREA_H_

// C++ Includes
#include <vector>
#include <algorithm>
#include <iostream>

#include <json/value.h>

// SDL Includes

// Map Includes
#include "../utils/logger.h"

#include "../IDisplay.h"

#include "Tile.h"

namespace mapping {
/**
 * The DrawingArea class contains the map being drawn (or loaded, or displayed)
 */
class DrawingArea: public display::IDisplay {
public:
	//! Constructor that defines the display area of the map
	DrawingArea(int offsetX, int offsetY, int height, int width,
			SDL_Renderer* renderer);

	//! Render the drawing area
	void render();

	//! Handle an SDL Event
	void handleEvents(SDL_Event event);

	//! Set the current texture
	/*!
	 * Sets the texture to display under the mouse cursor
	 * @param texture This should always actually be a utils::Image, but every texture is stored as utils::MapTexture
	 */
	void setCurTexture(utils::MapTexture *texture);

	//! Temporary (ish) method for scrolling the map area
	void scrollDrawingArea(int x, int y);

	// TODO mossro: Update this temporary function
	//! Loads a map
	/*!
	 * Currently initial implementation to be updated. Takes a vector of the map, clears the map then loads this one
	 * @param tiles Vector of tiles, which is copied into an internal vector
	 */
	void loadMap(std::vector<Tile*> loadedTiles);

	//! Gets the map vector, used for saving
	/*!
	 *
	 * @return Returns the map vector
	 */
	std::vector<Tile*>* getMap();

	//! Clears the map
	void clearMap(int height, int width);

private:

	//! Current scaling applied to the drawing area
	int scale = 20;

	//! Allowed gap from edge of map to border of the display area
	int border = 0;

	//! Texture displayed under the mouse cursor
	utils::MapTexture *texture = NULL;

	//! The actual map
	std::vector<Tile*> tiles;

	//! Map Area (not the same as areaRect from display::IDisplay)
	SDL_Rect mapArea;
	//! Current view's x location
	int viewX;
	//! Current view's y location
	int viewY;

	//! current x location of the mouse converted to a tile location
	int tileX = 0;
	//! current y location of the mouse converted to a tile location
	int tileY = 0;
};

} /* namespace mapping */
#endif /* DRAWINGAREA_H_ */
