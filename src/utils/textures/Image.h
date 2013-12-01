/*
 * Image.h
 *
 *  Created on: 30 Nov 2013
 *      Author: Robin
 */

#ifndef IMAGE_H_
#define IMAGE_H_

// C++ Includes

// SDL Includes

// Map Includes
#include "../../MapConstants.h"

#include "../MapTextures.h"
#include "../logger.h"

namespace utils {

class Image: public MapTexture {
public:
	Image(SDL_Renderer* renderer);
	bool loadImage(std::string file);
};

} /* namespace utils */
#endif /* IMAGE_H_ */
