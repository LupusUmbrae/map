/*
 * DialogBox.h
 *
 *  Created on: 26 Dec 2013
 *      Author: Robin
 */

#ifndef DIALOGBOX_H_
#define DIALOGBOX_H_

// C++ Includes

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../IDisplay.h"

#include "../utils/MapTextures.h"
#include "../utils/logger.h"

#include "../actions/ActionQueue.h"
#include "../actions/ActionDialog.h"

namespace menu {

enum dialog {
	MESSAGE, YES_NO, INPUT
};

class DialogBox: public display::IDisplay {
public:
	DialogBox(int offsetX, int offsetY, int height, int width,
			utils::MapTexture* title, utils::MapTexture* message, dialog type,
			bool blocking, SDL_Renderer* renderer);
	~DialogBox();

	void render();
	void handleEvents(SDL_Event event);
	bool inArea(int x, int y);

	bool accepted();

	static void setImages(utils::MapTexture* ok, utils::MapTexture* yes,
			utils::MapTexture* no);


private:
	static utils::MapTexture* ok;
	static utils::MapTexture* yes;
	static utils::MapTexture* no;

	SDL_Rect* okRect = new SDL_Rect();
	SDL_Rect* yesRect = new SDL_Rect();
	SDL_Rect* noRect = new SDL_Rect();


	void addTitleAndMessage();
	void drawItems();

	utils::MapTexture* title;
	utils::MapTexture* message;
	dialog type = MESSAGE;
	bool blocking;

	bool acccept;

};

} /* namespace menu */
#endif /* DIALOGBOX_H_ */
