/*
 * Text.cpp
 *
 *  Created on: 1 Dec 2013
 *      Author: Robin
 */

#include "Text.h"

namespace utils {

Text::Text(SDL_Renderer* renderer) {
	this->renderer = renderer;
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

bool Text::convertSurface(SDL_Surface* textSurface) {
	bool success = true;
	if (textSurface != NULL) {

		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL) {
			logSDLError(std::cerr, "CreateTextureFromSurface in text");
			success = false;
		}
		width = textSurface->w;
		height = textSurface->h;

		SDL_FreeSurface(textSurface);

		MapTexture::loadedTextures.push_back(this);
	} else {
		logSDLError(std::cerr, "RenderText_Solid in Text");
		success = false;
	}
	return success;
}

}
/* namespace utils */
