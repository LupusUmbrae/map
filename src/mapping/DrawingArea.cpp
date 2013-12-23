/*
 * DrawingArea.cpp
 *
 *  Created on: 18 Nov 2013
 *      Author: Robin
 */

#include "DrawingArea.h"

namespace mapping {

DrawingArea::DrawingArea(int offsetX, int offsetY, int height, int width,
		utils::MapTexture *texture) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;
	this->texture = texture;
	curY = 0;
	curX = 0;
}

void DrawingArea::render() {
	int x, y;

	for (Tile *curTile : tiles) {
		x = (curTile->x * scale) + areaRect->x;
		y = (curTile->y * scale) + areaRect->y;
		curTile->texture->render(x, y, scale, scale);
	}

	x = (curX * scale) + areaRect->x;
	y = (curY * scale) + areaRect->y;

	texture->render(x, y, scale, scale);
}

void DrawingArea::handleEvents(SDL_Event event) {

	if (event.type == SDL_MOUSEMOTION) {
		curX = (event.motion.x - areaRect->x) / scale;
		curY = (event.motion.y - areaRect->y) / scale;

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

		Tile *newTile = new Tile(curX, curY, texture);

		bool found = false;
		for (size_t i = 0; i < tiles.size(); i++) {
			if (tiles[i]->x == curX && tiles[i]->y == curY) {
				found = true;
				break;
			}
		}

		if (!found) {
			tiles.push_back(newTile);
		}

	}

	if (rightDown) {
		Tile* tile;
		for (size_t i = 0; i < tiles.size(); i++) {
			if (tiles[i]->x == curX && tiles[i]->y == curY) {
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

Json::Value DrawingArea::save() {
	Json::Value root;

	root["name"] = "testSAve";
	root["version"] = "v0.1";

	Tile* tile;
	for (size_t i = 0; i < tiles.size(); i++) {
		tile = tiles.at(i);

		root["map"][i]["name"] = *tile->texture->getUniqueName();
		root["map"][i]["x"] = tile->x;
		root["map"][i]["y"] = tile->y;
	}

	return root;
}

void DrawingArea::clearMap() {
	this->tiles.clear();
}

} /* namespace mapping */
