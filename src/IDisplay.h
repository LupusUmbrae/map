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

class IDisplay {
public:
	IDisplay();
	virtual ~IDisplay() {};

	virtual void render() = 0;
	virtual void handleEvents(SDL_Event event) = 0;

	virtual bool inArea(int x, int y);
	void mouseUp(Uint8 button);

protected:
	bool leftDown = false;
	bool rightDown = false;
	int curX = 0;
	int curY = 0;

	SDL_Renderer* renderer;
	SDL_Rect *areaRect = new SDL_Rect();
};

} /* namespace display */
#endif /* IDISPLAY_H_ */
