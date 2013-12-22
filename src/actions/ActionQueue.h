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

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "IAction.h"

namespace action {

class ActionQueue {
public:
	static ActionQueue& getInstance()
	{
		static ActionQueue instance;
		return instance;
	}

	void addAction(IAction* action);
	IAction* pollEvent();

private:
	std::queue<IAction*> actionQueue;
};

} /* namespace action */
#endif /* ACTIONQUEUE_H_ */
