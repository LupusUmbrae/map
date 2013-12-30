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

namespace utils {

class Image: public MapTexture {
public:
	//! Constructor
	/*!
	 *
	 * @param renderer Global renderer
	 */
	Image(SDL_Renderer* renderer);

	/*!
	 * Load an image from file
	 * @param file Location of the image file
	 * @return True if image was successfully loaded
	 */
	bool loadImage(std::string file);
};

} /* namespace utils */
#endif /* IMAGE_H_ */
