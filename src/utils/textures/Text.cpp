/*
 * Text.cpp
 *
 *  Created on: 1 Dec 2013
 *      Author: Robin
 */

#include "utils/textures/Text.h"

namespace utils {

SDL_Color Text::color = { 0, 0, 0 };
TTF_Font* Text::font = nullptr;

void Text::setDefaults(SDL_Color color, TTF_Font* font)
{
	Text::color = color;
	Text::font = font;
}

Text::Text(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

bool Text::createText(std::string text) {
	bool success = true;

	SDL_Surface* textSurface;

	if (font != nullptr) {
		textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		success = this->convertSurface(textSurface);
	} else {
		success = false;
	}

	return success;
}

bool Text::createText(std::string text, SDL_Color color, SDL_Color bgColor,
		TTF_Font* font) {
	bool success = true;

	SDL_Surface* textSurface;

	textSurface = TTF_RenderText_Shaded(font, text.c_str(), color, bgColor);

	success = this->convertSurface(textSurface);

	return success;
}

bool Text::createText(std::string text, SDL_Color color, TTF_Font* font) {
	bool success = true;

	SDL_Surface* textSurface;

	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	success = this->convertSurface(textSurface);

	return success;
}

}
/* namespace utils */
