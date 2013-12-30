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
#include <vector>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../IDisplay.h"

#include "InputBox.h"

#include "../utils/MapTextures.h"
#include "../utils/textures/Text.h"
#include "../utils/logger.h"

#include "../actions/ActionQueue.h"
#include "../actions/IAction.h"

namespace menu {

enum dialog {
	MESSAGE, /** < An information dialog box, only has an OK Button */
	YES_NO, /** < A choice dialog box, user can click yes or no*/
	INPUT /** < Allows for user input (not implemented)*/
};

/**
 * This class creates a dialog box for display
 */
class DialogBox: public display::IDisplay {
public:
	//! Sets the dialog box button images
	static void setImages(utils::MapTexture* ok, utils::MapTexture* yes,
			utils::MapTexture* no);

	//! Construct a dialog box using the given text textures
	/*!
	 *
	 * @param offsetX X offset for the display
	 * @param offsetY Y offset for the display
	 * @param height height of the display
	 * @param width width of the display
	 * @param title Title texture of the dialog box
	 * @param message Message texture of the dialog box
	 * @param type dialog type
	 * @param blocking Disable all lower layers
	 * @param renderer global renderer
	 * @param actionType Action to send back
	 */
	DialogBox(int offsetX, int offsetY, int height, int width,
			utils::MapTexture* title, utils::MapTexture* message, dialog type,
			bool blocking, SDL_Renderer* renderer, action::actions actionType);

	//! Construct a dialog box and create new Text texture from the given strings
	/*!
	 *
	 * @param offsetX X offset for the display
	 * @param offsetY Y offset for the display
	 * @param height height of the display
	 * @param width width of the display
	 * @param title Title string to make into a texture
	 * @param message Message string to make into a texture
	 * @param type dialog type
	 * @param blocking Disable all lower layers
	 * @param renderer global renderer
	 * @param actionType Action to send back
	 */
	DialogBox(int offsetX, int offsetY, int height, int width,
			std::string title, std::string message, dialog type, bool blocking,
			SDL_Renderer* renderer, action::actions actionType);

	~DialogBox();

	//! Render the drawing area
	void render();

	//! Handle an SDL Event
	void handleEvents(SDL_Event event);

	//! Overriden in area check,
	/*!
	 * If blocking is set to true this will return true without checking, otherwise calls display::IDisplay::inArea(int x, int y)
	 * @param x current mouse x
	 * @param y current mouse y
	 * @return True if in area
	 */
	bool inArea(int x, int y);

	//! Was the dialog box accepted
	bool accepted();

	void addInput(InputBox* input);

	std::string findInput(std::string name);

protected:
	//! Static button image
	static utils::MapTexture* ok;
	//! Static button image
	static utils::MapTexture* yes;
	//! Static button image
	static utils::MapTexture* no;

	//! action to be passed to the queue
	action::IAction action;
	//! What action should be sent
	action::actions actionType;

	//! Title of the dialog box
	utils::MapTexture* title;

	//! Message of this dialog box
	utils::MapTexture* message;

	std::vector<InputBox*> inputs;
private:
	//! area for the ok Button
	SDL_Rect* okRect = new SDL_Rect();
	//! area for the yes Button
	SDL_Rect* yesRect = new SDL_Rect();
	//! area for the no Button
	SDL_Rect* noRect = new SDL_Rect();

	//! draw the items on the dialog box
	/*!
	 * As the dialog box display is fairly static this draws all the items (aka. sets their SDL_Rects)
	 */
	void drawItems();

	//! Handle events if this is a message dialog box
	void handleEventsMessage(SDL_Event event);
	//! Handle events if this is a Yes/No dialog box
	void handleEventsYesNo(SDL_Event event);
	//! Handle events if this is a input dialog box
	void handleEventsInput(SDL_Event event);

	//! what type is this dialog box
	dialog type = MESSAGE;

	size_t inputTo = -1;

	//! Should this dialog box block all lower layers?
	/*!
	 * This prevents events going to any other display::IDisplay that has a lower z-index that this dialog box
	 */
	bool blocking;

	//! was a yes or a no pressed?
	bool acccept;

};

} /* namespace menu */
#endif /* DIALOGBOX_H_ */
