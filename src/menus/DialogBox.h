/*
 * DialogBox.h
 *
 *  Created on: 26 Dec 2013
 *      Author: Robin
 */

#ifndef DIALOGBOX_H_
#define DIALOGBOX_H_

// C++ Includes
#include <string>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../IDisplay.h"

#include "../utils/MapTextures.h"
#include "../utils/textures/Text.h"
#include "../utils/logger.h"

#include "../actions/ActionQueue.h"
#include "../actions/IAction.h"

namespace menu {

enum dialog {
	MESSAGE, YES_NO, INPUT
};

class DialogBox: public display::IDisplay {
public:
	DialogBox(int offsetX, int offsetY, int height, int width,
			utils::MapTexture* title, utils::MapTexture* message, dialog type,
			bool blocking, SDL_Renderer* renderer, action::actions actionType);

	DialogBox(int offsetX, int offsetY, int height, int width,
				std::string title, std::string message, dialog type,
				bool blocking, SDL_Renderer* renderer, action::actions actionType);

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

	action::IAction action;
	action::actions actionType;

	SDL_Rect* okRect = new SDL_Rect();
	SDL_Rect* yesRect = new SDL_Rect();
	SDL_Rect* noRect = new SDL_Rect();

	void drawItems();

	void handleEventsMessage(SDL_Event event);
	void handleEventsYesNo(SDL_Event event);
	void handleEventsInput(SDL_Event event);

	utils::MapTexture* title;
	utils::MapTexture* message;
	dialog type = MESSAGE;
	bool blocking;

	bool acccept;

};

} /* namespace menu */
#endif /* DIALOGBOX_H_ */
