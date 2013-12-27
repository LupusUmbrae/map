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
#include <SDL2/SDL_ttf.h>

// Map Includes
#include "../logger.h"
#include "../MapTextures.h"

namespace utils {

class Text: public utils::MapTexture {
public:
	Text(SDL_Renderer* renderer);
	bool createText(std::string text);
	bool createText(std::string text, SDL_Color color, TTF_Font* font);
	bool createText(std::string text, SDL_Color color, SDL_Color bgColor,
			TTF_Font* font);

	static void setDefaults(SDL_Color color, TTF_Font* font);
private:
	bool convertSurface(SDL_Surface* textSurface);
	static SDL_Color color;
	static TTF_Font* font;
};

} /* namespace utils */
#endif /* TEXT_H_ */
