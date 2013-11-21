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

	std::vector<MenuItem*> items;

	/*
	 * Load textures
	 */

	tile = loadTexture("resources/tile.bmp", renderer);
	tile2 = loadTexture("resources/tile2.bmp", renderer);

	/*
	 *  Create the display areas
	 */

	// Menus
	topMenu = new TopMenu(20, items, renderer);

	// Drawing Areas
	drawingArea = new mapping::DrawingArea(0, 20, SCREEN_HEIGHT - 20,
			SCREEN_WIDTH, tile);

	displays.push_back(topMenu);
	displays.push_back(drawingArea);

	return true;
}

void Map::logSDLError(std::ostream &os, const std::string &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void Map::cleanUp() {

	SDL_DestroyTexture(tile);
	SDL_DestroyTexture(tile2);
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

void Map::handleEvent(SDL_Event event) {

	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.type == SDL_MOUSEMOTION) {

			curX = event.motion.x;
			curY = event.motion.y;
		}
		for (display::IDisplay *display : displays) {
			if (display->inArea(curX, curY)) {
				display->handleEvents(event);
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		for (display::IDisplay *display : displays) {
			display->mouseUp(event.button.button);
		}
	}

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_1) {
			drawingArea->setCurTexture(tile);
		}

		if (event.key.keysym.sym == SDLK_2) {
			drawingArea->setCurTexture(tile2);
		}
	}
}

void Map::render() {
	for (display::IDisplay *display : displays) {
		display->render(renderer);
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

	curPointerTexture = tile;

	SDL_Event event;

	while (quit == false) {
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event)) {
			map.handleEvent(event);
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		map.render();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);

	}

	map.cleanUp();

	return 0;
}
