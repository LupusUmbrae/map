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

class DrawingArea: public display::IDisplay {
public:
	DrawingArea(int offsetX, int offsetY, int height, int width,
			utils::MapTexture *texture, SDL_Renderer* renderer);

	void render();
	void handleEvents(SDL_Event event);
	void setCurTexture(utils::MapTexture *texture);

	void scrollDrawingArea(int x, int y);

	// TODO mossro: Update this temporary function
	void loadMap(std::vector<Tile*> tiles);

	Json::Value save();

	void clearMap();

private:

	int scale = 20;

	int border = 0;

	utils::MapTexture *texture = NULL;

	std::vector<Tile*> tiles;

	SDL_Rect mapArea;
	int viewX;
	int viewY;

	int tileX = 0;
	int tileY = 0;
};

} /* namespace mapping */
#endif /* DRAWINGAREA_H_ */
