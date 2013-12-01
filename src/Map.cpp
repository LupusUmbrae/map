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

/**
 *
 */
bool Map::init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "IMG_Init Error: " << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
		return false;
	}

	screen = SDL_CreateWindow("My game", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(screen, -1, 0);

	if (renderer == NULL) {
		logSDLError(std::cout, "Create renderer failed");
	}

	SDL_SetWindowFullscreen(screen, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	if (screen == NULL) {
		return false;
	}

	std::vector<menu::MenuItem*> items;

	/*
	 * Fonts
	 */

	font = TTF_OpenFont("resources/lazy.ttf", 10);
	if (font == NULL) {
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		return false;
	}

	/*
	 * Load textures
	 */
	tile = new utils::Image(renderer);
	tile2 = new utils::Image(renderer);
	menuNew = new utils::Image(renderer);
	menuNewHover = new utils::Image(renderer);
	menuSave = new utils::Image(renderer);
	menuSaveHover = new utils::Image(renderer);

	logSDLError(std::cout, "hello?");

	tile->loadImage("resources/tile.bmp");
	tile2->loadImage("resources/tile2.bmp");

	menuNew->loadImage("resources/menus/new.bmp");
	menuNewHover->loadImage("resources/menus/newHover.bmp");

	menuSave->loadImage("resources/menus/save.bmp");
	menuSaveHover->loadImage("resources/menus/saveHover.bmp");


	loadedTextures.push_back(tile);
	loadedTextures.push_back(tile2);
	loadedTextures.push_back(menuNew);
	loadedTextures.push_back(menuNewHover);
	loadedTextures.push_back(menuSave);
	loadedTextures.push_back(menuSaveHover);

	/*
	 *  Create the display areas
	 */

	// Menus
	menu::MenuItem* menuNewItem = new menu::MenuItem("new", "tooltip New", NULL,
			menuNew, menuNewHover);
	menu::MenuItem* menuSaveItem = new menu::MenuItem("save", "tooltip Save",
			NULL, menuSave, menuSaveHover);

	items.push_back(menuNewItem);
	items.push_back(menuSaveItem);

	topMenu = new menu::TopMenu(0, 0, 24, SCREEN_WIDTH, items, font, renderer);

	menu::LeftMenu* leftMenu = new menu::LeftMenu(0, 24, SCREEN_HEIGHT - 24,
			200, renderer);

	// Drawing Areas
	drawingArea = new mapping::DrawingArea(200, 24, SCREEN_HEIGHT - 24,
			SCREEN_WIDTH - 200, tile);

	displays.push_back(topMenu);
	displays.push_back(drawingArea);
	displays.push_back(leftMenu);

	return true;
}

void Map::cleanUp() {

	for (utils::MapTexture* curTex : loadedTextures) {
		curTex->unload();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	SDL_Quit();
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
		display->render();
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