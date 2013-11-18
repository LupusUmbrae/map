/*
 * Map.cpp
 *
 *  Created on: 10 Nov 2013
 *      Author: Robin
 */

#include "Map.h"

Map::Map() {

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

bool Map::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	screen = SDL_CreateWindow("My game", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH,
			SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(screen, -1, 0);

	SDL_SetWindowFullscreen(screen, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	if (screen == NULL) {
		return false;
	}
	return true;
}

void Map::logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void Map::cleanUp() {

	SDL_DestroyTexture(tile);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	SDL_Quit();
}

/**
 *
 */
SDL_Texture* Map::loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = NULL;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != NULL) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == NULL) {
			this->logSDLError(std::cout, "CreateTextureFromSurface");
		}

	} else {
		this->logSDLError(std::cout, "LoadBmp");
	}

	return texture;
}

void Map::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Map::handleEvent() {

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
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftDown = false;
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			rightDown = false;
		}
	}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_1) {
			curPointerTexture = tile;
		}

		if (event.key.keysym.sym == SDLK_2) {
			curPointerTexture = tile2;
		}
	}

	if (leftDown) {

		SDL_Rect *tileLoc = new SDL_Rect;
		tileLoc->x = curX;
		tileLoc->y = curY;

		Tile *newTile = new Tile(tileLoc, curPointerTexture);
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

int main(int argc, char* args[]) {
	//Start SDL
	Map map;

	bool quit = false;

	if (!map.init()) {
		return 1;
	}

	//int height, std::vector<MenuItem*> menuItems, SDL_Renderer* renderer
	std::vector<MenuItem*> items;
	topMenu = new TopMenu(20, items, renderer);

	tile = map.loadTexture("tile.bmp", renderer);
	tile2 = map.loadTexture("tile2.bmp", renderer);

	curPointerTexture = tile;

	while (quit == false) {
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event)) {
			map.handleEvent();
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		map.renderTexture(curPointerTexture, renderer, curX * 20, curY * 20);

		for (Tile *curTile : tiles) {
			map.renderTexture(curTile->texture, renderer,
					curTile->location->x * 20, curTile->location->y * 20);
		}

		topMenu->renderMenu(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);

	}

	map.cleanUp();

	return 0;
}
