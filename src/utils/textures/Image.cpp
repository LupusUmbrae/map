/*
 * Image.cpp
 *
 *  Created on: 30 Nov 2013
 *      Author: Robin
 */

#include "Image.h"

namespace utils {

Image::Image(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

bool Image::loadImage(std::string file) {
	bool success = true;

	SDL_Surface *loadedImage = IMG_Load(file.c_str());

	if (renderer == NULL) {
		logSDLError(std::cout, "renderer null in image");
	}

	if (loadedImage != NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		if (texture == NULL) {

			logSDLError(std::cout, "CreateTextureFromSurface");
			success = false;
		}
		width = loadedImage->w;
		height = loadedImage->h;

		SDL_FreeSurface(loadedImage);
	} else {
		logSDLError(std::cout, "LoadBmp");
		success = false;
	}
	return success;
}

} /* namespace utils */
