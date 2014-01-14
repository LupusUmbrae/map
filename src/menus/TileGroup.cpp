/*
 * TileGroup.cpp
 *
 *  Created on: 8 Dec 2013
 *      Author: Robin
 */

#include "menus/TileGroup.h"

namespace menu {

utils::MapTexture* TileGroup::groupOpen = NULL;
utils::MapTexture* TileGroup::groupClosed = NULL;

void TileGroup::setImages(utils::MapTexture* groupOpen,
		utils::MapTexture* groupClosed) {
	TileGroup::groupOpen = groupOpen;
	TileGroup::groupClosed = groupClosed;
}

TileGroup::TileGroup(utils::MapTexture* groupName, std::vector<MenuItem*> tiles,
		SDL_Renderer* renderer) {
	this->groupName = groupName;
	this->tiles = tiles;
	this->renderer = renderer;
}

void TileGroup::handleEvents(SDL_Event event) {

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (this->open) {

				SDL_Rect* tileRect;
				MenuItem* tileItem;

				for (auto itemIter = tileMap.begin(); itemIter != tileMap.end();
						++itemIter) {

					tileRect = itemIter->first;
					tileItem = itemIter->second;

					if (curX >= tileRect->x
							&& (curX <= (tileRect->x + scale))) {
						if (curY >= tileRect->y
								&& (curY <= (tileRect->y + scale))) {
							action::ActionQueue::getInstance().addAction(
									&tileItem->action);
							break;
						}
					}
				}
			}

			if (curX >= nameRect->x && (curX <= (nameRect->x + 10))) {
				if (curY >= nameRect->y && (curY <= (nameRect->y + 10))) {
					this->open = !this->open;
					this->changed = true;
				}
			}

			for (TileGroup* curGroup : subGroups) {
				curGroup->handleEvents(event);
			}
		}
	}
}

void TileGroup::render() {
	SDL_Rect* tileRect;
	MenuItem* tileItem;

	if (open) {
		groupOpen->render(nameRect->x, nameRect->y, 10, 10);
	} else {
		groupClosed->render(nameRect->x, nameRect->y, 10, 10);
	}
	groupName->render(nameRect->x + 20, nameRect->y);

	if (open) {
		for (auto itemIter = tileMap.begin(); itemIter != tileMap.end();
				++itemIter) {
			tileRect = itemIter->first;
			tileItem = itemIter->second;

			tileItem->getIcon()->render(tileRect->x, tileRect->y, scale, scale);
		}

		for (TileGroup* curGroup : subGroups) {
			curGroup->render();
		}
	}

}

int TileGroup::redraw(int x, int y, int w) {
	areaRect->x = x;
	areaRect->y = y;
	areaRect->w = w;

	draw();
	this->changed = false;
	return areaRect->h;
}

void TileGroup::addGroup(std::vector<MenuItem*> newGroup,
		std::string category) {
	utils::Text* groupName = new utils::Text(renderer);
	groupName->createText(category);

	TileGroup* group = new TileGroup(groupName, newGroup, renderer);
	subGroups.push_back(group);
}

bool TileGroup::hasChanged() {
	changed = this->changed;

	if (!changed) {
		for (TileGroup* curGroup : subGroups) {
			changed = curGroup->hasChanged();
			if (changed) {
				break;
			}
		}
	}

	return changed;
}

bool TileGroup::isOpen() {
	return this->open;
}

void TileGroup::draw() {
	int renX = this->areaRect->x;
	int renY = this->areaRect->y;

	int SPACER = 5;

	int startX;
	int startY;

	startX = renX;
	startY = renY;

	renX += 5;
	renY += 5;

	nameRect->x = renX;
	nameRect->y = renY;

	if (open) {
		tileMap.clear();

		renY += 15;

		SDL_Rect* tileRect;

		for (MenuItem* curItem : tiles) {
			tileRect = new SDL_Rect();

			tileRect->x = renX;
			tileRect->y = renY;
			tileMap.insert(std::make_pair(tileRect, curItem));
			renX += scale + SPACER;

			if (renX >= (areaRect->w - (scale + SPACER))) {
				renX = this->areaRect->x + SPACER;
				renY += scale + SPACER;
			}
		}

		renY += scale;

		for (TileGroup* curGroup : subGroups) {
			renY += curGroup->redraw(startX + 5, renY, areaRect->w - 5);
		}
	} else {
		renY += 10;
	}

	areaRect->x = startX;
	areaRect->y = startY;

	areaRect->h = renY - startY;
}

} /* namespace menu */
