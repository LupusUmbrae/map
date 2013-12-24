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


	if (loadedImage != NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		if (texture == NULL) {

			logSDLError(std::cout, "CreateTextureFromSurface");
			success = false;
		}
		width = loadedImage->w;
		height = loadedImage->h;

		SDL_FreeSurface(loadedImage);

		MapTexture::loadedTextures.push_back(this);
	} else {
		logSDLError(std::cout, "LoadBmp");
		success = false;
	}
	return success;
}

} /* namespace utils */
