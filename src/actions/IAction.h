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
	NONE=0, CHANGE_TILE=1, NEW=2, SAVE=3, LOAD=4, CLOSE=5
};

class IAction {
public:
	IAction();
	IAction(actions action);
	IAction(actions action, void* object);

	actions getAction();
	void setAction(actions action);

	void* getObject();
	void setObject(void* object);

protected:
	actions action;
	void* object;
};

} /* namespace action */
#endif /* IACTION_H_ */
