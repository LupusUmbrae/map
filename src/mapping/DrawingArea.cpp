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
}

void DrawingArea::render(SDL_Renderer* renderer) {
	for (Tile *curTile : tiles) {
		this->renderTexture(curTile->texture, renderer,
				curTile->location->x * 20, curTile->location->y * 20);
	}

	this->renderTexture(texture, renderer, curX * 20, curY * 20);
}

void DrawingArea::handleEvents(SDL_Event event) {

	if (event.type == SDL_MOUSEMOTION) {
		curX = event.motion.x / 20;
		curY = event.motion.y / 20;
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
		for (size_t i = 0; i < tiles.size(); i++) {
			SDL_Rect *curTile = tiles[i]->location;
			if (curTile->x == curX && curTile->y == curY) {
				tiles.erase(tiles.begin() + i);
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
