/*
 * ActionDialog.h
 *
 *  Created on: 26 Dec 2013
 *      Author: Robin
 */

#ifndef ACTIONDIALOG_H_
#define ACTIONDIALOG_H_

// C++ Includes

// SDL Includes

// Map Includes
#include "IAction.h"

#include "../IDisplay.h"

namespace action {

class ActionDialog: public action::IAction {
public:
	ActionDialog(display::IDisplay* display);
	virtual ~ActionDialog();

	display::IDisplay* getDisplay();

private:
	display::IDisplay* display;
};

} /* namespace menu */
#endif /* ACTIONDIALOG_H_ */
