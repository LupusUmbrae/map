/*
 * DrawingArea.cpp
 *
 *  Created on: 18 Nov 2013
 *      Author: Robin
 */

#include "DrawingArea.h"

namespace mapping {

DrawingArea::DrawingArea(int offsetX, int offsetY, int height, int width,
		SDL_Texture *texture) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;
	this->texture = texture;
	curY = 0;
	curX = 0;
}

void DrawingArea::render(SDL_Renderer* renderer) {
	int x, y;
	for (Tile *curTile : tiles) {
		x = (curTile->location->x * 20) + areaRect->x;
		y = (curTile->location->y * 20) + areaRect->y;
		this->renderTexture(curTile->texture, renderer, x, y);
	}

	x = (curX * 20) + areaRect->x;
	y = (curY * 20) + areaRect->y;

	this->renderTexture(texture, renderer, x, y);
}

void DrawingArea::handleEvents(SDL_Event event) {

	if (event.type == SDL_MOUSEMOTION) {
		curX = (event.motion.x - areaRect->x) / 20;
		curY = (event.motion.y - areaRect->y) / 20;

	}

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftDown = true;
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			rightDown = true;
		}
	}

	if (leftDown) {
		SDL_Rect *tileLoc = new SDL_Rect;
		tileLoc->x = curX;
		tileLoc->y = curY;

		Tile *newTile = new Tile(tileLoc, texture);
		tiles.push_back(newTile);
	}

	if (rightDown) {
		Tile* tile;
		for (size_t i = 0; i < tiles.size(); i++) {
			SDL_Rect *curTile = tiles[i]->location;
			if (curTile->x == curX && curTile->y == curY) {
				tile = tiles.at(i);
				tiles.erase(tiles.begin() + i);
				delete tile;
				break;
			}

		}
	}
}

void DrawingArea::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x,
		int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void DrawingArea::setCurTexture(SDL_Texture *texture) {
	this->texture = texture;
}

} /* namespace mapping */
