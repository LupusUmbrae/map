/*
 * JsonProcessor.h
 *
 *  Created on: 30 Dec 2013
 *      Author: Robin
 */

#ifndef JSONPROCESSOR_H_
#define JSONPROCESSOR_H_

// C++ Includes
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>

#include <json/json.h>

// SDL Includes
#include <SDL2/SDL.h>

// Map Includes
#include "../menus/TileGroup.h"
#include "../mapping/Tile.h"
#include "textures/Image.h"
#include "textures/Text.h"

namespace utils {

class JsonProcessor {
public:
	JsonProcessor(SDL_Renderer* renderer, TTF_Font* font);
	virtual ~JsonProcessor();

	std::vector<menu::TileGroup*> loadTilesets(std::string rootDir);
	std::vector<Tile*> loadMap(std::string saveFile);
	std::string saveMap(std::vector<Tile*>* map);

private:
	TTF_Font* font;
	SDL_Renderer* renderer;

};

} /* namespace menu */
#endif /* JSONPROCESSOR_H_ */
