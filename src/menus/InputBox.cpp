/*
 * InputBox.cpp
 *
 *  Created on: 30 Dec 2013
 *      Author: Robin
 */

#include "InputBox.h"

namespace menu {

InputBox::InputBox(SDL_Renderer* renderer, std::string name) {
	this->renderer = renderer;
	this->renderedText = new utils::Text(renderer);
	renderedText->createText(" ");

	this->name = name;
	this->renderedName = new utils::Text(renderer);
	renderedName->createText(name);

	areaRect->x = 0;
	areaRect->y = 0;
	areaRect->w = 0;
	areaRect->h = 0;
}

InputBox::~InputBox() {
	// TODO Auto-generated destructor stub
}

void InputBox::handleEvents(SDL_Event event) {

	if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
		inputText.pop_back();
		reRender = true;
	} else if (event.type == SDL_TEXTINPUT) {
		if (!((event.text.text[0] == 'v' || event.text.text[0] == 'V')
				&& (SDL_GetModState() & KMOD_CTRL))) {
			inputText += event.text.text;
			reRender = true;
		}
	}

	if (reRender) {
		if (!inputText.empty()) {
			renderedText->createText(inputText);
		} else {
			renderedText->createText(" ");
		}
	}
}

void InputBox::render() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, areaRect);

	if (renderedText == NULL) {
		logMessage("its null");
	}

	renderedName->render(areaRect->x, areaRect->y);
	renderedText->render(areaRect->x + renderedName->getWidth() + 10, areaRect->y);
}

void InputBox::setArea(int x, int y, int w, int h) {
	areaRect->x = x;
	areaRect->y = y;
	areaRect->w = w;
	areaRect->h = h;
}

bool InputBox::inArea(int x, int y) {
	if (x >= areaRect->x && (x <= (areaRect->x + areaRect->w))) {
		if (y >= areaRect->y && (y <= (areaRect->y + areaRect->h))) {
			return true;
		}
	}
	return false;
}

} /* namespace menu */
