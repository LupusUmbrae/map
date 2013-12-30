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
	mapArea.w = 30;
	mapArea.h = 30;

	viewX = 0;
	viewY = 0;

}

void DrawingArea::render() {
	int x, y;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, areaRect);

	SDL_Rect curArea;

	curArea.x = -viewX;
	curArea.y = -viewY;
	curArea.w = mapArea.w - (viewX + (areaRect->w / scale));
	curArea.h = mapArea.h - (viewY + (areaRect->h / scale));

	if (-viewX < 0) {
		curArea.x = areaRect->x;
	} else {
		curArea.x = areaRect->x + (curArea.x * scale);
	}

	if (curArea.y < 0) {
		curArea.y = areaRect->y;
	} else {
		curArea.y = areaRect->y + (curArea.y * scale);
	}

	if (curArea.w > 0) {
		curArea.w = areaRect->w;
		if (mapArea.w < (areaRect->h / scale)) {
			curArea.w = (mapArea.w * scale);
		}
	} else {
		curArea.w = ((areaRect->w / scale) + curArea.w) * scale;
	}

	if (curArea.h > 0) {
		curArea.h = areaRect->h;
		if ((mapArea.h * scale) < areaRect->h) {
			curArea.h = mapArea.h * scale;
		}
	} else {
		curArea.h = ((areaRect->h / scale) + curArea.h) * scale;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &curArea);

	for (Tile *curTile : tiles) {
		x = (curTile->x * scale);
		y = (curTile->y * scale);

		if ((x >= (viewX * scale) && x < ((viewX * scale) + areaRect->w))
				&& (y >= (viewY * scale) && y < ((viewY * scale) + areaRect->h))) {

			// Correct locations within the actual screen
			x += areaRect->x - (viewX * scale);
			y += areaRect->y - (viewY * scale);
			curTile->texture->render(x, y, scale, scale);
		}

	}

	x = (tileX - viewX) * scale;
	x += areaRect->x;

	y = (tileY - viewY) * scale;
	y += areaRect->y;

	if (texture != NULL) {
		texture->render(x, y, scale, scale);
	}

}

void DrawingArea::handleEvents(SDL_Event event) {

	if (event.type == SDL_MOUSEMOTION) {
		tileX = ((event.motion.x - areaRect->x) / scale) + viewX;
		tileY = ((event.motion.y - areaRect->y) / scale) + viewY;

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
			if ((tileX >= 0 && tileX < mapArea.w)
					&& (tileY >= 0 && tileY < mapArea.h)) {
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
	viewX += x;
	viewY += y;

	if (viewX < (0 - border)) {
		viewX = 0 - (border);
	} else if ((viewX + (areaRect->w / scale)) > (mapArea.w + border)) {
		viewX = (mapArea.w + border) - (areaRect->w / scale);
	}

	if (viewY < (0 - border)) {
		viewY = 0 - border;
	} else if ((viewY + (areaRect->h / scale)) > (mapArea.h + border)) {
		viewY = (mapArea.h + border) - (areaRect->h / scale);
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
