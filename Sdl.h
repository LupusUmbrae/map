/*
 * Sdl.h
 *
 *  Created on: 10 Nov 2013
 *      Author: Robin
 */

#ifndef SDL_H_
#define SDL_H_

#include <string.h>
#include <iostream>
#include <ostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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


// tiles
std::vector<SDL_Rect*> tiles;
bool rightDown = false;
bool leftDown = false;

class Sdl {
public:
	Sdl();
	virtual ~Sdl();

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