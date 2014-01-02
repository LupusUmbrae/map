/*
 * Map.cpp
 *
 *  Created on: 10 Nov 2013
 *      Author: Robin
 */

#include "Map.h"

/*!
 *  \brief text
 */
Map::Map() {
	// Give the displays the first row, the add to display wont handle this
	displaysNew.push_back((std::vector<display::IDisplay*>()));
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

	SDL_Color color = { 0, 0, 0 }; // black text
	SDL_Color bgColor = { 255, 255, 255 }; // white background

	utils::Text::setDefaults(color, font);

	/*
	 * Find tile sets
	 */

	jsonProcessor = new utils::JsonProcessor(renderer);
	std::vector<menu::TileGroup*> groups = jsonProcessor->loadTilesets(
			"resources/tilesets/");

	/*
	 * Load static textures
	 */
	utils::Image* groupOpen = new utils::Image(renderer);
	utils::Image* groupClosed = new utils::Image(renderer);

	utils::Image* menuNew = new utils::Image(renderer);
	utils::Image* menuNewHover = new utils::Image(renderer);

	utils::Image* menuSave = new utils::Image(renderer);
	utils::Image* menuSaveHover = new utils::Image(renderer);

	utils::Image* menuLoad = new utils::Image(renderer);
	utils::Image* menuLoadHover = new utils::Image(renderer);

	utils::Image* ok = new utils::Image(renderer);
	utils::Image* yes = new utils::Image(renderer);
	utils::Image* no = new utils::Image(renderer);

	menuNew->loadImage("resources/menus/new.bmp");
	menuNewHover->loadImage("resources/menus/newHover.bmp");

	menuSave->loadImage("resources/menus/save.bmp");
	menuSaveHover->loadImage("resources/menus/saveHover.bmp");

	menuLoad->loadImage("resources/menus/load.png");
	menuLoadHover->loadImage("resources/menus/loadHover.png");

	groupOpen->loadImage("resources/menus/minus.png");
	groupClosed->loadImage("resources/menus/cross.png");

	ok->loadImage("resources/menus/ok.png");
	yes->loadImage("resources/menus/yes.png");
	no->loadImage("resources/menus/no.png");

	utils::Text* newTooltip = new utils::Text(renderer);
	utils::Text* saveTooltip = new utils::Text(renderer);
	utils::Text* loadTooltip = new utils::Text(renderer);

	newTooltip->createText("New map", color, bgColor, font);
	saveTooltip->createText("Save map", color, bgColor, font);
	loadTooltip->createText("Load map", color, bgColor, font);

	/*
	 *  Create the display areas
	 */

	menu::DialogBox::setImages(ok, yes, no);

	// Top Menu
	std::vector<menu::MenuItem*> items;

	menu::MenuItem* menuNewItem = new menu::MenuItem("new", newTooltip,
			action::IAction(action::NEW), menuNew, menuNewHover);
	menu::MenuItem* menuSaveItem = new menu::MenuItem("save", saveTooltip,
			action::IAction(action::SAVE), menuSave, menuSaveHover);
	menu::MenuItem* menuLoadItem = new menu::MenuItem("load", loadTooltip,
			action::IAction(action::LOAD), menuLoad, menuLoadHover);

	items.push_back(menuNewItem);
	items.push_back(menuSaveItem);
	items.push_back(menuLoadItem);

	topMenu = new menu::TopMenu(0, 0, 24, SCREEN_WIDTH, items, renderer);

	// Side menu
	menu::LeftMenu* leftMenu = new menu::LeftMenu(0, 24, SCREEN_HEIGHT - 24,
			200, renderer, groups, groupClosed, groupOpen);

	// Drawing Areas
	drawingArea = new mapping::DrawingArea(200, 24, SCREEN_HEIGHT - 24,
			SCREEN_WIDTH - 200, renderer);

	addToDisplay(topMenu);
	addToDisplay(drawingArea);
	addToDisplay(leftMenu);

	return true;
}

void Map::run() {
	bool quit = false;

	SDL_Event event;
	action::IAction action;
	SDL_StartTextInput();
	while (quit == false) {
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event)) {
			this->handleEvent(event);
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		while (action::ActionQueue::getInstance().pollEvent(&action)) {
			handleAction(action);
		}

		this->render();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderPresent(renderer);

	}
	SDL_StopTextInput();
	this->cleanUp();
}

void Map::cleanUp() {

	for (utils::MapTexture* curTex : utils::MapTexture::loadedTextures) {
		curTex->~MapTexture();
		delete curTex;
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
		for (size_t i = (displaysNew.size()); i-- > 0;) {
			for (display::IDisplay *display : displaysNew.at(i)) {
				if (display->inArea(curX, curY)) {
					display->handleEvents(event);
					return;
				}
			}
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		for (size_t i = (displaysNew.size()); i-- > 0;) {
			for (display::IDisplay *display : displaysNew.at(i)) {
				display->mouseUp(event.button.button);
			}
		}
		return;
	}

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			drawingArea->scrollDrawingArea(0, -1);
			break;
		case SDLK_DOWN:
			drawingArea->scrollDrawingArea(0, 1);
			break;
		case SDLK_LEFT:
			drawingArea->scrollDrawingArea(-1, 0);
			break;
		case SDLK_RIGHT:
			drawingArea->scrollDrawingArea(1, 0);
			break;
		}

	}

	if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
		for (size_t i = (displaysNew.size()); i-- > 0;) {
			for (display::IDisplay *display : displaysNew.at(i)) {
				if (display->inArea(curX, curY)) {
					display->handleEvents(event);
					return;
				}
			}
		}
	}
}

void Map::handleAction(action::IAction action) {
	display::IDisplay* display;
	utils::MapTexture* tile;

	menu::DialogBox* dialog;
	menu::InputBox* input;

	std::string saveRoot;

	std::ofstream saveFile;

	std::vector<Tile*> loadedMap;

	int x;
	int y;

	switch (action.getAction()) {
	case action::NONE:
		logMessage("None action received");
		break;
	case action::CHANGE_TILE:
		tile = reinterpret_cast<utils::MapTexture*>(action.getObject());
		drawingArea->setCurTexture(tile);
		break;
	case action::NEW:

		if (action.getObject() == nullptr) {
			dialog = new menu::DialogBox(300, 100, 100, 200, "New Map",
					"Enter new map tile size", menu::INPUT, true, renderer,
					action::NEW);
			input = new menu::InputBox(renderer, "height");
			dialog->addInput(input);
			input = new menu::InputBox(renderer, "width");
			dialog->addInput(input);

			addToDisplay(dialog, 3);

		} else {
			dialog = reinterpret_cast<menu::DialogBox*>(action.getObject());

			x = atoi(dialog->findInput("width").c_str());
			y = atoi(dialog->findInput("height").c_str());

			drawingArea->clearMap(y, x);

			removeDisplay(dialog);
		}

		break;
	case action::SAVE:

		if (action.getObject() == nullptr) {
			addToDisplay(
					new menu::DialogBox(300, 100, 60, 200, "Save",
							"Are you sure you want to save?", menu::YES_NO,
							true, renderer, action::SAVE), 3);
		} else {
			dialog = reinterpret_cast<menu::DialogBox*>(action.getObject());

			if (dialog->accepted()) {
				saveRoot = jsonProcessor->saveMap(drawingArea->getMap(),
						drawingArea->getWidth(), drawingArea->getHieght());
				saveFile.open("resources/save.json");
				if (saveFile) {
					saveFile << saveRoot;
					saveFile.close();
				}
			}

			removeDisplay(dialog);
		}

		break;
	case action::LOAD:

		loadedMap = jsonProcessor->loadMap("resources/save.json");

		if (loadedMap.empty()) {
			logMessage("Save file had no map");
		} else {
			drawingArea->clearMap(jsonProcessor->getMapHeight(),
					jsonProcessor->getMapWidth());
			drawingArea->loadMap(loadedMap);
		}

		break;
	case action::CLOSE:
		display = reinterpret_cast<display::IDisplay*>(action.getObject());
		this->removeDisplay(display);
		break;
	default:
		logMessage("Unknown event");
		break;
	}
}

void Map::render() {
	/*
	 * The outer vector depicts layers, the positon in the vector represents the z-index
	 */
	for (size_t i = 0; i < (displaysNew.size()); i++) {
		for (size_t j = 0; j < displaysNew.at(i).size(); j++) {
			displaysNew.at(i).at(j)->render();
		}
	}
}

void Map::addToDisplay(display::IDisplay* display, unsigned int zIndex) {
	// Check the vector exists
	if (displaysNew.size() <= zIndex) {
		for (size_t i = displaysNew.size(); i <= zIndex; i++) {
			displaysNew.push_back(std::vector<display::IDisplay*>());
		}
	}

	displaysNew.at(zIndex).push_back(display);
}

void Map::removeDisplay(display::IDisplay* display) {

	bool found = false;
	for (size_t i = (displaysNew.size()); i-- > 0;) {
		for (size_t j = 0; j < displaysNew.at(i).size(); j++) {
			if (displaysNew.at(i).at(j) == display) {
				displaysNew.at(i).erase(displaysNew.at(i).begin() + j);
				found = true;
				delete display;
				break;
			}
			if (found) {
				break;
			}
		}
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
