/*
 * Sdl.h
 *
 *  Created on: 10 Nov 2013
 *      Author: Robin
 */

#ifndef SDL_H_
#define SDL_H_

// C++ Includes
#include <string.h>
#include <iostream>
#include <ostream>
#include <vector>

// SDL Includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Map Includes

#include "mapping/Tile.h"

#include "menus/TopMenu.h"
#include "menus/LeftMenu.h"
#include "menus/MenuItem.h"

#include "mapping/DrawingArea.h"

/*
 * Actual code
 */


// Screeeeeen
const int SCREEN_WIDTH = 648;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// me window
SDL_Window *screen = NULL;
SDL_Renderer *renderer = NULL;

int curX = 0, curY = 0;

// textures
std::vector<SDL_Texture*> textures;
SDL_Texture* tile = NULL;
SDL_Texture* tile2 = NULL;

SDL_Texture* menuNew = NULL;
SDL_Texture* menuNewHover = NULL;

SDL_Texture* menuSave = NULL;
SDL_Texture* menuSaveHover = NULL;

SDL_Texture* curPointerTexture = NULL;

// tiles
std::vector<Tile*> tiles;
bool rightDown = false;
bool leftDown = false;



class Map {
public:
	Map();
	virtual ~Map();

	bool init();
	bool run(); // TODO
	void cleanUp();
	void logSDLError(std::ostream &os, const std::string &msg);

	void applySurface(int x, int y, SDL_Surface* source,
			SDL_Surface* destination);
	void handleEvent(SDL_Event event);
	void render();
	void renderClean();

	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

private:
	int curX = 0, curY = 0;

	//Displays
	menu::TopMenu* topMenu = NULL;

	mapping::DrawingArea* drawingArea = NULL;
	//SDL_Renderer *renderer = NULL;

	std::vector<display::IDisplay*> displays;
	TTF_Font* font;
};

#endif /* SDL_H_ */
