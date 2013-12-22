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
	NONE=0, CHANGE_TILE=1
};

class IAction {
public:
	IAction();
	void setAction(actions action);
	actions getAction();

protected:
	actions action;
};

} /* namespace action */
#endif /* IACTION_H_ */
