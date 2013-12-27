/*
 * IAction.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: Robin
 */

#include "IAction.h"

namespace action {

IAction::IAction() {
	this->action = NONE;
	this->object = nullptr;
}

IAction::IAction(actions action) {
	this->action = action;
	this->object = nullptr;
}

IAction::IAction(actions action, void* object) {
	this->action = action;
	this->object = object;
}

actions IAction::getAction() {
	return this->action;
}

void IAction::setAction(actions action) {
	this->action = action;
}

void* IAction::getObject() {
	return this->object;
}

void IAction::setObject(void* object) {
	this->object = object;
}

} /* namespace action */
