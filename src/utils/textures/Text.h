/*
 * Text.h
 *
 *  Created on: 1 Dec 2013
 *      Author: Robin
 */

#ifndef TEXT_H_
#define TEXT_H_

// C++ Includes
#include <string>
#include <ostream>

// SDL Includes

// Map Includes
#include "../logger.h"
#include "../MapTextures.h"

namespace utils {

class Text: public utils::MapTexture {
public:
	Text(SDL_Renderer* renderer);
	bool createText(std::string text, SDL_Color color, TTF_Font* font);
	bool createText(std::string text, SDL_Color color, SDL_Color bgColor,
			TTF_Font* font);
private:
	bool convertSurface(SDL_Surface* textSurface);
};

} /* namespace utils */
#endif /* TEXT_H_ */
