/*
 * DrawingArea.cpp
 *
 *  Created on: 18 Nov 2013
 *      Author: Robin
 */

#include "DrawingArea.h"

namespace mapping {

DrawingArea::DrawingArea(int offsetX, int offsetY, int height, int width,
		SDL_Renderer* renderer) {
	this->renderer = renderer;
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;
	this->texture = NULL; // do not start with a texture loaded
	tileY = 0;
	tileX = 0;

	mapArea.x = 0;
	mapArea.y = 0;
	mapArea.w = 800;
	mapArea.h = 500;

	viewX = 0;
	viewY = 0;

}

void DrawingArea::render() {
	int x, y;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	SDL_Rect curArea;

	curArea.x = -viewX;
	curArea.y = -viewY;
	curArea.w = mapArea.w - viewX;
	curArea.h = mapArea.h - viewY;

	if (curArea.x < 0) {
		curArea.x = areaRect->x;
	} else {
		curArea.x += areaRect->x;
	}

	if (curArea.y < 0) {
		curArea.y = areaRect->y;
	} else {
		curArea.y += areaRect->y;
	}

	if (curArea.w > 0) {
		curArea.w = areaRect->w;
	} else {
		curArea.w = areaRect->w + curArea.w;
	}

	if (curArea.h > 0) {
		curArea.h = areaRect->h;
	} else {
		curArea.h = areaRect->h + curArea.h;
	}

	SDL_RenderDrawRect(renderer, &curArea);

	for (Tile *curTile : tiles) {
		x = (curTile->x * scale);
		y = (curTile->y * scale);

		if ((x >= viewX && x < (viewX + scale + areaRect->w))
				&& (y >= viewY && y < (viewY + scale + areaRect->h))) {

			// Correct locations within the actual screen
			x += areaRect->x - viewX;
			y += areaRect->y - viewY;
			curTile->texture->render(x, y, scale, scale);
		}

	}

	x = (tileX * scale) + areaRect->x - viewX;
	y = (tileY * scale) + areaRect->y - viewY;

	if (texture != NULL) {
		texture->render(x, y, scale, scale);
	}

}

void DrawingArea::handleEvents(SDL_Event event) {

	if (event.type == SDL_MOUSEMOTION) {
		tileX = (event.motion.x - areaRect->x + viewX) / scale;
		tileY = (event.motion.y - areaRect->y + viewY) / scale;

	}

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftDown = true;
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			rightDown = true;
		}
	}

	if (event.type == SDL_MOUSEWHEEL) {
		scale += event.wheel.y;
		if (scale < 10) {
			scale = 10;
		} else if (scale > 100) {
			scale = 100;
		}
	}

	if (leftDown) {
		if (texture != NULL) {
			if ((tileX >= mapArea.x && (tileX + scale) <= mapArea.w)
					&& (tileY >= mapArea.y && (tileY + scale) <= mapArea.h)) {

				Tile *newTile = new Tile(tileX, tileY, texture);

				bool found = false;
				for (size_t i = 0; i < tiles.size(); i++) {
					if (tiles[i]->x == tileX && tiles[i]->y == tileY) {
						found = true;
						break;
					}
				}

				if (!found) {
					tiles.push_back(newTile);
				}
			}
		}
	}

	if (rightDown) {
		Tile* tile;
		for (size_t i = 0; i < tiles.size(); i++) {
			if (tiles[i]->x == tileX && tiles[i]->y == tileY) {
				tile = tiles.at(i);
				tiles.erase(tiles.begin() + i);
				delete tile;
				break;
			}
		}
	}
}

void DrawingArea::setCurTexture(utils::MapTexture *texture) {
	this->texture = texture;
}

void DrawingArea::scrollDrawingArea(int x, int y) {
	viewX += x * scale;
	viewY += y * scale;

	if (viewX < (0 - (border * scale))) {
		viewX = 0 - (border * scale);
	} else if (viewX > (mapArea.w + (border * scale))) {
		viewX = mapArea.w + (border * scale);
	}

	if (viewY < (0 - (border * scale))) {
		viewY = 0 - (border * scale);
	} else if (viewY > (mapArea.h + (border * scale))) {
		viewY = mapArea.h + (border * scale);
	}
}

void DrawingArea::loadMap(std::vector<Tile*> loadedTiles) {
	this->tiles.clear();

	this->tiles.insert(this->tiles.end(), loadedTiles.begin(),
			loadedTiles.end());

	loadedTiles.clear();
}

std::vector<Tile*>* DrawingArea::getMap() {
	return &tiles;
}

void DrawingArea::clearMap(int height, int width) {
	this->tiles.clear();
	mapArea.x = 0;
	mapArea.y = 0;
	mapArea.w = width;
	mapArea.h = height;
}

} /* namespace mapping */
