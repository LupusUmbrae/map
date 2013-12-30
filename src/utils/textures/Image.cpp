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


	success = this->convertSurface(loadedImage);

	return success;
}

} /* namespace utils */
