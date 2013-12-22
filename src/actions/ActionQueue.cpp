/*
 * ActionQueue.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#include "ActionQueue.h"

namespace action {

void ActionQueue::addAction(IAction* action) {
	actionQueue.push(action);
}

IAction* ActionQueue::pollEvent() {
	IAction* action;
	if (!actionQueue.empty()) {

		action = actionQueue.front();
		actionQueue.pop();
		return action;
	}
	return NULL;
}

} /* namespace action */
