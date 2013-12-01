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
#include <iostream>

// Map Includes
#include "../utils/logger.h"

#include "../IDisplay.h"

#include "Tile.h"

namespace mapping {

class DrawingArea: public display::IDisplay {
public:
	DrawingArea(int offsetX, int offsetY, int height, int width, utils::MapTexture *texture);

	void render();
	void handleEvents(SDL_Event event);
	void setCurTexture(utils::MapTexture *texture);

private:
	int curX = 0, curY = 0;

	utils::MapTexture *texture = NULL;

	std::vector<Tile*> tiles;

};

} /* namespace mapping */
#endif /* DRAWINGAREA_H_ */
