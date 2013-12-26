/*
 * IAction.h
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#ifndef IACTION_H_
#define IACTION_H_

// C++ Includes

// SDL Includes

// Map Includes

namespace action {

/*!
 * NONE - do nothing, if this is called its due to an error somehwere
 * Change Tile - Change the currently selected tile in the drawing area
 * New - Create a new map
 * Save - save a map
 * Load - load a map
 * Close - Close the given display (i.e. remove it from the displays)
 */
enum actions {
	NONE, CHANGE_TILE, NEW, SAVE, LOAD, CLOSE
};

class IAction {
public:
	IAction();
	IAction(actions action);

	actions getAction();

protected:
	actions action;
};

} /* namespace action */
#endif /* IACTION_H_ */
