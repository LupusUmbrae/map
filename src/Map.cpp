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
	 * Find tile sets
	 */

	SDL_Color color = { 0, 0, 0 }; // black text
	SDL_Color bgColor = { 255, 255, 255 }; // white background

	Json::Reader reader;
	Json::Value root;

	std::vector<menu::TileGroup*> groups;
	std::vector<utils::MapTexture*> tiles;
	menu::TileGroup* curGroup;
	utils::Image* curTile;
	utils::Text* groupName;

	DIR* dir;
	struct dirent* ent;

	std::stringstream setFolder;
	std::stringstream jsonFolder;
	std::stringstream imageLocation;
	std::stringstream uniqueName;

	// TODO mossro: improve this.. thing, also probably move to a new class
	if ((dir = opendir("resources/tilesets/")) != NULL) {
		std::ifstream ifile;
		while ((ent = readdir(dir)) != NULL) {
			setFolder.str("");
			jsonFolder.str("");

			setFolder << "resources/tilesets/" << ent->d_name;
			jsonFolder << setFolder.str() << "/set.json";

			ifile.open(jsonFolder.str(), std::ifstream::in); // marked as error but compiles
			if (ifile) {
				if (reader.parse(ifile, root)) {
					tiles.clear();
					// Create tile set
					groupName = new utils::Text(renderer);
					groupName->createText(root["name"].asString(), color, font);

					Json::Value imagesToLoad = root["tiles"];
					for (size_t i = 0; i < imagesToLoad.size(); i++) {
						curTile = new utils::Image(renderer);

						uniqueName.str("");
						imageLocation.str("");

						imageLocation << setFolder.str() << "/"
								<< imagesToLoad[0].get("filename", "").asString();
						uniqueName << ent->d_name << "."
								<< imagesToLoad[0].get("name", "").asString();

						curTile->loadImage(imageLocation.str());
						curTile->setUniqueName(uniqueName.str());
						tiles.push_back(curTile);
						loadedTextures.push_back(curTile);
					}
					curGroup = new menu::TileGroup(groupName, tiles);
					groups.push_back(curGroup);

				} else {
					logMessage(reader.getFormattedErrorMessages());
				}

			}
		}
	}

	/*
	 * Load textures
	 */
	utils::Image* groupOpen = new utils::Image(renderer);
	utils::Image* groupClosed = new utils::Image(renderer);

	utils::Image* menuNew;
	utils::Image* menuNewHover;

	utils::Image* menuSave;
	utils::Image* menuSaveHover;

	utils::Image* menuLoad;
	utils::Image* menuLoadHover;

	tile = new utils::Image(renderer);
	tile2 = new utils::Image(renderer);
	stone = new utils::Image(renderer);
	menuNew = new utils::Image(renderer);
	menuNewHover = new utils::Image(renderer);
	menuSave = new utils::Image(renderer);
	menuSaveHover = new utils::Image(renderer);
	menuLoad = new utils::Image(renderer);
	menuLoadHover = new utils::Image(renderer);

	tile->loadImage("resources/tile.bmp");
	tile2->loadImage("resources/tile2.bmp");
	stone->loadImage("resources/tiles/stone.png");

	menuNew->loadImage("resources/menus/new.bmp");
	menuNewHover->loadImage("resources/menus/newHover.bmp");

	menuSave->loadImage("resources/menus/save.bmp");
	menuSaveHover->loadImage("resources/menus/saveHover.bmp");

	menuLoad->loadImage("resources/menus/load.png");
	menuLoadHover->loadImage("resources/menus/loadHover.png");

	groupOpen->loadImage("resources/menus/minus.png");
	groupClosed->loadImage("resources/menus/cross.png");

	loadedTextures.push_back(tile);
	loadedTextures.push_back(tile2);
	loadedTextures.push_back(stone);
	loadedTextures.push_back(menuNew);
	loadedTextures.push_back(menuNewHover);
	loadedTextures.push_back(menuSave);
	loadedTextures.push_back(menuSaveHover);
	loadedTextures.push_back(menuLoad);
	loadedTextures.push_back(menuLoadHover);
	loadedTextures.push_back(groupOpen);
	loadedTextures.push_back(groupClosed);

	utils::Text* newTooltip = new utils::Text(renderer);
	utils::Text* saveTooltip = new utils::Text(renderer);
	utils::Text* loadTooltip = new utils::Text(renderer);

	//utils::Text* groupName = new utils::Text(renderer);

	newTooltip->createText("New map", color, bgColor, font);
	saveTooltip->createText("Save map", color, bgColor, font);
	loadTooltip->createText("Load map", color, bgColor, font);

//	groupName->createText("Group One", color, font);

	loadedTextures.push_back(newTooltip);
	loadedTextures.push_back(saveTooltip);

	/*
	 *  Create the display areas
	 */

	// Menus
	std::vector<menu::MenuItem*> items;

	menu::MenuItem* menuNewItem = new menu::MenuItem("new", newTooltip,
			new action::IAction(action::NEW), menuNew, menuNewHover);
	menu::MenuItem* menuSaveItem = new menu::MenuItem("save", saveTooltip,
			new action::IAction(action::SAVE), menuSave, menuSaveHover);
	menu::MenuItem* menuLoadItem = new menu::MenuItem("load", loadTooltip,
			new action::IAction(action::LOAD), menuLoad, menuLoadHover);

	items.push_back(menuNewItem);
	items.push_back(menuSaveItem);
	items.push_back(menuLoadItem);

	topMenu = new menu::TopMenu(0, 0, 24, SCREEN_WIDTH, items, font, renderer);

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

	}
}

void Map::handleAction(action::IAction* action) {
	action::ActionTile* tileAction;

	Json::Reader reader;
	Json::Value mapRoot;
	Json::Value saveRoot;

	std::ifstream ifile;
	std::ofstream saveFile;

	Tile* loadedTile;
	utils::MapTexture* texture;
	std::vector<Tile*> loadedMap;

	std::string tileName;
	int x;
	int y;

	switch (action->getAction()) {
	case action::NONE:
		logMessage("None action received");
		break;
	case action::CHANGE_TILE:
		tileAction = static_cast<action::ActionTile*>(action);
		drawingArea->setCurTexture(tileAction->getTexture());
		break;
	case action::NEW:
		drawingArea->clearMap();
		break;
	case action::SAVE:

		saveRoot = drawingArea->save();

		saveFile.open("resources/save.json");
		if (saveFile) {
			saveFile << saveRoot;
			saveFile.close();
		}

		break;
	case action::LOAD:

		/*
		 * TODO mossro: Move this else where
		 */

		ifile.open("resources/save.json");
		if (ifile) {
			if (reader.parse(ifile, mapRoot)) {
				if (mapRoot["version"].asString().compare("v0.1") == 0) {
					Json::Value tiles = mapRoot["map"];
					for (Json::Value tile : tiles) {
						logMessage(tile["name"].asString());
						tileName = tile["name"].asString();
						for (utils::MapTexture* curTex : loadedTextures) {
							if (curTex->getUniqueName()->compare(tileName)  == 0) {
								texture = curTex;
								break;
							}
						}
						x = tile["x"].asInt();
						y = tile["y"].asInt();
						loadedTile = new Tile(x, y, texture);
						loadedMap.push_back(loadedTile);
					}
					drawingArea->loadMap(loadedMap);
				}
			} else {
				logMessage(reader.getFormattedErrorMessages());
			}
		}

		/*
		 * END TODO..
		 */

		break;
	default:
		logMessage("Unknown event");
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
