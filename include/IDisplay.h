/*
 * IDisplay.h
 *
 *  Created on: 18 Nov 2013
 *      Author: Robin
 */

#ifndef IDISPLAY_H_
#define IDISPLAY_H_

// C++ Includes
#include <iostream>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes

namespace display {
/**
 * This class must be inherited by all displays
 */
class IDisplay {
public:

	IDisplay();
	virtual ~IDisplay() {
	}
	;

	//! A pure virtual member. Used to make displays render
	virtual void render() = 0;

	//! A pure virtual member. Used to send displays events
	/*!
	 * This is called by Map when a display needs to handle an event
	 * @param event SDL event to be handled
	 */
	virtual void handleEvents(SDL_Event event) = 0;

	//! Virtual member. Used to check if the mouse is in this diplay area
	/*!
	 * Map uses this method to check if an event occured in this display area
	 * @param x current mouses x position over the window
	 * @param y current mouses y position over the window
	 * @return if the mouses x,y are within the bounds of this display
	 */
	virtual bool inArea(int x, int y);

	//! Called to signal mouse buttons have been released
	/*!
	 *
	 * @param button Which button on the mouse have been released
	 */
	void mouseUp(Uint8 button);

protected:
	//! Flag for left mouse button being down
	bool leftDown = false;
	//! Flag for right mouse button being down
	bool rightDown = false;
	//! Current x location of the mouse
	int curX = 0;
	//! Current y location of the mouse
	int curY = 0;

	//! pointer to the global renderer
	SDL_Renderer* renderer;
	//! Bounding box for the display
	SDL_Rect *areaRect = new SDL_Rect();
};

} /* namespace display */
#endif /* IDISPLAY_H_ */
