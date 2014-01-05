/*
 * ActionQueue.h
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#ifndef ACTIONQUEUE_H_
#define ACTIONQUEUE_H_

// C++ Includes
#include <queue>
#include <iostream>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "IAction.h"

namespace action {
/**
 * Action queue is a singleton used to pass actions from any class back to Map for processing. This allows cross class communication.
 */
class ActionQueue {
public:
	//! Static access to the ActionQueue
	/*!
	 *
	 * @return Sataic instance of the ActionQueue
	 */
	static ActionQueue& getInstance() {
		static ActionQueue instance;
		return instance;
	}

	//! Add an action to the queue
	/*!
	 *
	 * @param action Action to be added
	 */
	void addAction(IAction* action);

	//! Get the next action and remove it from the queue
	/*!
	 * Gets the front of the queue and sets the given pointers, pointer to the action before popping the queue.
	 * @param action Action pointer to be replaced
	 * @return True if there is an action to process
	 */
	bool pollEvent(IAction* action);

private:
	//! Queue that stores the actions
	std::queue<IAction*> actionQueue;
};

} /* namespace action */
#endif /* ACTIONQUEUE_H_ */
