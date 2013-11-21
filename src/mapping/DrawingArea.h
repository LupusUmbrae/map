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


#include "../IDisplay.h"
#include "Tile.h"

namespace mapping {

class DrawingArea: public display::IDisplay {
public:
	DrawingArea(int offsetX, int offsetY, int height, int width, SDL_Texture *texture);

	void render(SDL_Renderer* renderer);
	void handleEvents(SDL_Event event);
	void setCurTexture(SDL_Texture *texture);

private:
	int curX = 0, curY = 0;

	SDL_Texture *texture = NULL;

	std::vector<Tile*> tiles;

	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
};

} /* namespace mapping */
#endif /* DRAWINGAREA_H_ */
