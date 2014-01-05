/*
 * ActionQueue.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#include "actions/ActionQueue.h"

namespace action {

void ActionQueue::addAction(IAction* action) {
	actionQueue.push(action);
}

bool ActionQueue::pollEvent(IAction* action) {
	if (!actionQueue.empty()) {
		*action = *actionQueue.front();
		actionQueue.pop();
		return true;
	}
	return false;
}

} /* namespace action */
