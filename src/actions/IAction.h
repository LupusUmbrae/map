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

//! Enum of possible actions
enum actions {
	NONE, /**<do nothing, if this is called its due to an error somehwere */
	CHANGE_TILE, /**<Change the currently selected tile in the drawing area */
	NEW, /**<Create a new map */
	SAVE, /**<save a map */
	LOAD, /**<load a map */
	CLOSE /**<Close the given display (i.e. remove it from the displays) */
};

/**
 * Action class used to wrap all actions types
 */
class IAction {
public:
	//! Default constructor
	IAction();
	//! Construct with a specific action
	IAction(actions action);
	//! Construct with a specific action and an object
	IAction(actions action, void* object);

	//! Get the action
	actions getAction();
	//! Set the action
	void setAction(actions action);

	//! Get the object
	void* getObject();
	//! Set the object
	void setObject(void* object);

protected:
	actions action;

	/*!
	 * The void* allows the action to pass any require object it needs to through. Although Map must be expecting the object for the given action
	 */
	void* object;
};

} /* namespace action */
#endif /* IACTION_H_ */
