/*
 * ActionQueue.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#include "ActionQueue.h"

namespace action {

void ActionQueue::addAction(IAction* action) {
	std::cout << "action 1: " << action->getAction() << std::endl;
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
