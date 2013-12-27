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
		bool blocking, SDL_Renderer* renderer, action::actions actionType) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

	this->title = title;
	this->message = message;
	this->type = type;
	this->blocking = blocking;
	this->renderer = renderer;

	this->actionType = actionType;

	drawItems();
}

DialogBox::DialogBox(int offsetX, int offsetY, int height, int width,
		std::string title, std::string message, dialog type, bool blocking,
		SDL_Renderer* renderer, action::actions actionType) {
	areaRect->x = offsetX;
	areaRect->y = offsetY;
	areaRect->h = height;
	areaRect->w = width;

	utils::Text* newTitle = new utils::Text(renderer);
	newTitle->createText(title);

	utils::Text* newMessage = new utils::Text(renderer);
	newMessage->createText(message);

	this->title = newTitle;
	this->message = newMessage;
	this->type = type;
	this->blocking = blocking;
	this->renderer = renderer;

	this->actionType = actionType;

	drawItems();

}

DialogBox::~DialogBox() {
	title->unload();
	message->unload();
}

bool DialogBox::accepted() {
	return this->acccept;
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
			DialogBox::yes->render(yesRect->x, yesRect->y);
			DialogBox::no->render(noRect->x, noRect->y);
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
		switch (this->type) {
		case MESSAGE:
			this->handleEventsMessage(event);
			break;
		case YES_NO:
			this->handleEventsYesNo(event);
			break;
		case INPUT:
			this->handleEventsInput(event);
			break;
		}
	}
}

void DialogBox::handleEventsMessage(SDL_Event event) {

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {

			if (curX >= okRect->x && (curX <= (okRect->x + okRect->w))) {
				if (curY >= okRect->y && (curY <= (okRect->y + okRect->h))) {
					action.setAction(actionType);
					action.setObject(this);
					action::ActionQueue::getInstance().addAction(&action);
				}
			}

		}
	}
}

void DialogBox::handleEventsYesNo(SDL_Event event) {

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {

			if (curX >= yesRect->x && (curX <= (yesRect->x + yesRect->w))) {
				if (curY >= yesRect->y && (curY <= (yesRect->y + yesRect->h))) {
					this->acccept = true;
					action.setAction(actionType);
					action.setObject(this);
					action::ActionQueue::getInstance().addAction(&action);
				}
			} else if (curX >= noRect->x && (curX <= (noRect->x + noRect->w))) {
				if (curY >= noRect->y && (curY <= (noRect->y + noRect->h))) {
					this->acccept = false;
					action.setAction(actionType);
					action.setObject(this);
					action::ActionQueue::getInstance().addAction(&action);
				}
			}
		}
	}
}

void DialogBox::handleEventsInput(SDL_Event event) {

	action::ActionQueue::getInstance().addAction(&action);

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
			noRect->x = dialogRightX - DialogBox::no->getWidth();
			noRect->y = dialogY - DialogBox::no->getHeight();
			noRect->w = DialogBox::no->getWidth();
			noRect->h = DialogBox::no->getWidth();

			yesRect->x = noRect->x - DialogBox::yes->getWidth() - 10;
			yesRect->y = dialogY - DialogBox::yes->getHeight();
			yesRect->w = DialogBox::yes->getWidth();
			yesRect->h = DialogBox::yes->getWidth();
			break;
		case INPUT:
			logMessage("Not implemented");
			break;

		}
	}
}

} /* namespace menu */
