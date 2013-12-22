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

	return true;
}

bool Map::loadResources() {

	/*
	 * Fonts
	 */

	font = TTF_OpenFont("resources/lazy.ttf", 10);
	if (font == NULL) {
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		return false;
	}

	font2 = TTF_OpenFont("resources/lazy.ttf", 15);
	if (font == NULL) {
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		return false;
	}

	/*
	 * Load textures
	 */
	utils::Image* groupOpen = new utils::Image(renderer);
	utils::Image* groupClosed = new utils::Image(renderer);

	tile = new utils::Image(renderer);
	tile2 = new utils::Image(renderer);
	stone = new utils::Image(renderer);
	menuNew = new utils::Image(renderer);
	menuNewHover = new utils::Image(renderer);
	menuSave = new utils::Image(renderer);
	menuSaveHover = new utils::Image(renderer);

	tile->loadImage("resources/tile.bmp");
	tile2->loadImage("resources/tile2.bmp");
	stone->loadImage("resources/tiles/stone.png");

	menuNew->loadImage("resources/menus/new.bmp");
	menuNewHover->loadImage("resources/menus/newHover.bmp");

	menuSave->loadImage("resources/menus/save.bmp");
	menuSaveHover->loadImage("resources/menus/saveHover.bmp");

	groupOpen->loadImage("resources/menus/minus.png");
	groupClosed->loadImage("resources/menus/cross.png");

	loadedTextures.push_back(tile);
	loadedTextures.push_back(tile2);
	loadedTextures.push_back(stone);
	loadedTextures.push_back(menuNew);
	loadedTextures.push_back(menuNewHover);
	loadedTextures.push_back(menuSave);
	loadedTextures.push_back(menuSaveHover);
	loadedTextures.push_back(groupOpen);
	loadedTextures.push_back(groupClosed);

	SDL_Color color = { 0, 0, 0 }; // black text
	SDL_Color bgColor = { 255, 255, 255 }; // white background

	utils::Text* newTooltip = new utils::Text(renderer);
	utils::Text* saveTooltip = new utils::Text(renderer);

	utils::Text* groupName = new utils::Text(renderer);

	newTooltip->createText("New map", color, bgColor, font);
	saveTooltip->createText("Save map", color, bgColor, font);

	groupName->createText("Group One", color, font);

	loadedTextures.push_back(newTooltip);
	loadedTextures.push_back(saveTooltip);

	/*
	 *  Create the display areas
	 */

	// Menus
	std::vector<menu::MenuItem*> items;

	menu::MenuItem* menuNewItem = new menu::MenuItem("new", newTooltip, NULL,
			menuNew, menuNewHover);
	menu::MenuItem* menuSaveItem = new menu::MenuItem("save", saveTooltip, NULL,
			menuSave, menuSaveHover);

	items.push_back(menuNewItem);
	items.push_back(menuSaveItem);

	topMenu = new menu::TopMenu(0, 0, 24, SCREEN_WIDTH, items, font, renderer);

	std::vector<utils::MapTexture*> tiles;

	tiles.push_back(tile);
	tiles.push_back(tile2);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);
	tiles.push_back(stone);

	menu::TileGroup* group = new menu::TileGroup(groupName, tiles);
	menu::TileGroup* group2 = new menu::TileGroup(groupName, tiles);

	std::vector<menu::TileGroup*> groups;

	groups.push_back(group);
	groups.push_back(group2);

	menu::LeftMenu* leftMenu = new menu::LeftMenu(0, 24, SCREEN_HEIGHT - 24,
			200, renderer, groups, groupClosed, groupOpen);

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

void Map::handleEvent(SDL_Event event) {

	if (event.type != SDL_MOUSEBUTTONUP && event.type != SDL_KEYDOWN) {
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

		if (event.key.keysym.sym == SDLK_3) {
			drawingArea->setCurTexture(stone);
		}
	}
}

void Map::handleAction(action::IAction* action) {

	switch (action->getAction()) {
	case action::NONE:
		logMessage("None action received");
		break;
	case action::CHANGE_TILE:
		action::changeTile* tileAction =
				static_cast<action::changeTile*>(action);
		drawingArea->setCurTexture(tileAction->getTile());
		break;
	}
}

void Map::run() {
	bool quit = false;

	SDL_Event event;
	action::IAction* action;

	while (quit == false) {
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event)) {
			this->handleEvent(event);
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		action = action::ActionQueue::getInstance().pollEvent();
		while (action != NULL) {
			handleAction(action);
			delete action;
			action = action::ActionQueue::getInstance().pollEvent();
		}

		this->render();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);

	}

	this->cleanUp();
}

void Map::render() {
	for (display::IDisplay *display : displays) {
		display->render();
	}
}

int main(int argc, char* args[]) {
	//Start SDL
	Map map;

	if (!map.init()) {
		return 1;
	}

	if (!map.loadResources()) {
		return 1;
	}

	map.run();

	return 0;
}
