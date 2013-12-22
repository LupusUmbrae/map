/*
 * IAction.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#include "IAction.h"

namespace action {

IAction::IAction() {
}

IAction::IAction(actions action)
{
	this->action = action;
}

actions IAction::getAction() {
	return this->action;
}

} /* namespace action */
