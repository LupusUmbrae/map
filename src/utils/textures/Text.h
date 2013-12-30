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
#include "../MapTextures.h"

namespace utils {

class Text: public utils::MapTexture {
public:
	//! Constructor
	/*!
	 *
	 * @param renderer Global renderer
	 */
	Text(SDL_Renderer* renderer);

	//! Create text using default font and colour
	/*!
	 *
	 * @param text String to convert to a texture
	 * @return True if texture was created successfully
	 */
	bool createText(std::string text);

	//! Create a text texture
	/*!
	 *
	 * @param text String to convert to a texture
	 * @param color Colour if the text
	 * @param font font to be used
	 * @return True if texture was created successfully
	 */
	bool createText(std::string text, SDL_Color color, TTF_Font* font);

	//! Create a text texture with a background
	/*!
	 *
	 * @param text String to convert to a texture
	 * @param color Colour if the text
	 * @param bgColor Background colour
	 * @param font font to be used
	 * @return True if texture was created successfully
	 */
	bool createText(std::string text, SDL_Color color, SDL_Color bgColor,
			TTF_Font* font);

	//! Sets the default font and foreground colour to be used when creating text using the defaults
	/*!
	 *
	 * @param color Colour of the text
	 * @param font Font to be used
	 */
	static void setDefaults(SDL_Color color, TTF_Font* font);
private:

	//! Default colour
	static SDL_Color color;

	//! Default font
	static TTF_Font* font;

	//! width of the texture
	int width;
	//! height of the texture
	int height;

};

} /* namespace utils */
#endif /* TEXT_H_ */
