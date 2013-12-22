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

enum actions {
	NONE, CHANGE_TILE, NEW, SAVE
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
