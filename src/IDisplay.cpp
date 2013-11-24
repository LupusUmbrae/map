/*
 * IDisplay.cpp
 *
 *  Created on: 18 Nov 2013
 *      Author: Robin
 */

#include "IDisplay.h"

namespace display {

IDisplay::IDisplay() {
	// TODO Auto-generated constructor stub

}

bool IDisplay::inArea(int x, int y) {
	curX = x;
	curY = y;
	if (x >= areaRect->x && (x <= (areaRect->x + areaRect->w))) {
		if (y >= areaRect->y && (y <= (areaRect->y + areaRect->h))) {
			return true;
		}
	}
	return false;
}

void IDisplay::mouseUp(Uint8 button) {
	if (button == SDL_BUTTON_LEFT) {
		leftDown = false;
	}
	if (button == SDL_BUTTON_RIGHT) {
		rightDown = false;
	}
}

} /* namespace display */
