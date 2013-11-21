/*
 * IMenuAction.h
 *
 *  Created on: 17 Nov 2013
 *      Author: Robin
 */

#ifndef IMENUACTION_H_
#define IMENUACTION_H_

class IMenuAction {
public:
	IMenuAction();
	virtual ~IMenuAction() {};
	virtual bool action() = 0;
};

#endif /* IMENUACTION_H_ */
