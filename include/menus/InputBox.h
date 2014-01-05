/*
 * InputBox.h
 *
 *  Created on: 30 Dec 2013
 *      Author: Robin
 */

#ifndef INPUTBOX_H_
#define INPUTBOX_H_

// C++ Includes
#include <string>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../utils/textures/Text.h"

namespace menu {

class InputBox {
public:
	InputBox(SDL_Renderer* renderer, std::string name);
	virtual ~InputBox();

	void handleEvents(SDL_Event event);

	void render();

	void setArea(int x, int y, int w, int h);

	bool inArea(int x, int y);

	std::string getName() {
		return this->name;
	}

	std::string getInput() {
		return this->inputText;
	}

private:
	SDL_Renderer* renderer;
	std::string inputText = "";
	utils::Text* renderedText;

	std::string name;
	utils::Text* renderedName;

	SDL_Rect* areaRect = new SDL_Rect();

	bool reRender = false;
};

} /* namespace menu */
#endif /* INPUTBOX_H_ */
