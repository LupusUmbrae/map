/*
 * DialogBox.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: Robin
 */

#include "DialogBox.h"

namespace menu {

utils::MapTexture* DialogBox::ok = new utils::MapTexture();
utils::MapTexture* DialogBox::yes = new utils::MapTexture();
utils::MapTexture* DialogBox::no = new utils::MapTexture();

void DialogBox::setImages(utils::MapTexture* ok, utils::MapTexture* yes,
		utils::MapTexture* no) {
	DialogBox::ok = ok;
	DialogBox::yes = yes;
	DialogBox::no = no;
}

DialogBox::DialogBox(int offsetX, int offsetY, int height, int width,
		utils::MapTexture* title, utils::MapTexture* message, dialog type,
		bool blocking, SDL_Renderer* renderer) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

	this->title = title;
	this->message = message;
	this->type = type;
	this->blocking = blocking;
	this->renderer = renderer;

	drawItems();

}

DialogBox::~DialogBox() {
	title->unload();
	message->unload();
}

void DialogBox::addTitleAndMessage() {

}

void DialogBox::render() {
	SDL_SetRenderDrawColor(renderer, 0xE0, 0xE0, 0xE0, 0xFF);
	SDL_RenderFillRect(renderer, areaRect);

	title->render(areaRect->x, areaRect->y);
	message->render(areaRect->x, areaRect->y + title->getHeight());

	if (DialogBox::ok != NULL && DialogBox::yes != NULL && DialogBox::no != NULL) {
		switch (type) {
		case MESSAGE:
			DialogBox::ok->render(okRect->x, okRect->y);
			break;
		case YES_NO:
			logMessage("Not implemented");
			break;
		case INPUT:
			logMessage("Not implemented");
			break;

		}
	}
}

bool DialogBox::inArea(int x, int y) {
	this->curX = x;
	this->curY = y;
	if (blocking) {
		return true;
	}
	return IDisplay::inArea(x, y);
}

void DialogBox::handleEvents(SDL_Event event) {

	if (IDisplay::inArea(curX, curY)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {

				if (curX >= okRect->x && (curX <= (okRect->x + okRect->w))) {
					if (curY >= okRect->y
							&& (curY <= (okRect->y + okRect->h))) {
						action.setAction(action::CLOSE);
						action.setObject(this);
						action::ActionQueue::getInstance().addAction(&action);
					}
				}

			}
		}
	}
}

void DialogBox::drawItems() {
	if (DialogBox::ok != NULL && DialogBox::yes != NULL && DialogBox::no != NULL) {
		int dialogRightX = this->areaRect->x + this->areaRect->w - 10;
		int dialogY = this->areaRect->y + this->areaRect->h - 10;
		switch (type) {
		case MESSAGE:
			okRect->x = dialogRightX - DialogBox::ok->getWidth();
			okRect->y = dialogY - DialogBox::ok->getHeight();
			okRect->w = DialogBox::ok->getWidth();
			okRect->h = DialogBox::ok->getWidth();
			break;
		case YES_NO:
			logMessage("Not implemented");
			break;
		case INPUT:
			logMessage("Not implemented");
			break;

		}
	}
}

} /* namespace menu */
