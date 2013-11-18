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

// Map Includes
#include "Tile.h"


/*
 * Actual code
 */

#include "menus/TopMenu.h"
#include "menus/MenuItem.h"

// Screeeeeen
const int SCREEN_WIDTH = 648;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

// me window
SDL_Window *screen = NULL;
SDL_Renderer *renderer = NULL;

// event for handling..
SDL_Event event;

int curX = 0, curY = 0;

// textures
SDL_Texture* tile = NULL;
SDL_Texture* tile2 = NULL;

SDL_Texture* curPointerTexture = NULL;


// tiles
std::vector<Tile*> tiles;
bool rightDown = false;
bool leftDown = false;

//menus
TopMenu* topMenu = NULL;

class Map {
public:
	Map();
	virtual ~Map();

	bool init();
	void cleanUp();
	void logSDLError(std::ostream &os, const std::string &msg);

	void applySurface(int x, int y, SDL_Surface* source,
			SDL_Surface* destination);
	void handleEvent();

	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

};

#endif /* SDL_H_ */
