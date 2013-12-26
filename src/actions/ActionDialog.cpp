/*
 * ActionDialog.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: Robin
 */

#include "ActionDialog.h"

namespace action {

ActionDialog::ActionDialog(display::IDisplay* display) {
	this->display = display;
	this->action = action::CLOSE;

}

ActionDialog::~ActionDialog() {
	// TODO Auto-generated destructor stub
}

display::IDisplay* ActionDialog::getDisplay() {
	return this->display;
}

} /* namespace menu */
