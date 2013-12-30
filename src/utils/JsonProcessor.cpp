/*
 * JsonProcessor.cpp
 *
 *  Created on: 30 Dec 2013
 *      Author: Robin
 */

#include "JsonProcessor.h"

namespace utils {

JsonProcessor::JsonProcessor(SDL_Renderer* renderer, TTF_Font* font) {
	this->renderer = renderer;
	this->font = font;

}

JsonProcessor::~JsonProcessor() {
	// TODO Auto-generated destructor stub
}

std::vector<menu::TileGroup*> JsonProcessor::loadTilesets(std::string rootDir) {
	Json::Reader reader;
	Json::Value root;

	std::vector<menu::TileGroup*> groups;
	std::vector<utils::MapTexture*> tiles;
	menu::TileGroup* curGroup;
	utils::Image* curTile;
	utils::Text* groupName;

	DIR* dir;
	struct dirent* ent;

	std::stringstream setFolder;
	std::stringstream jsonFolder;
	std::stringstream imageLocation;
	std::stringstream uniqueName;

	SDL_Color color = { 0, 0, 0 }; // black text

	if ((dir = opendir(rootDir.c_str())) != NULL) {
		std::ifstream ifile;
		while ((ent = readdir(dir)) != NULL) {
			setFolder.str("");
			jsonFolder.str("");

			setFolder << "resources/tilesets/" << ent->d_name;
			jsonFolder << setFolder.str() << "/set.json";

			ifile.open(jsonFolder.str().c_str(), std::ifstream::in);
			if (ifile) {
				if (reader.parse(ifile, root)) {
					tiles.clear();
					// Create tile set
					groupName = new utils::Text(renderer);
					groupName->createText(root["name"].asString(), color, font);

					Json::Value imagesToLoad = root["tiles"];
					for (size_t i = 0; i < imagesToLoad.size(); i++) {
						curTile = new utils::Image(renderer);

						uniqueName.str("");
						imageLocation.str("");

						imageLocation << setFolder.str() << "/"
								<< imagesToLoad[0].get("filename", "").asString();
						uniqueName << ent->d_name << "."
								<< imagesToLoad[0].get("name", "").asString();

						curTile->loadImage(imageLocation.str());
						curTile->setUniqueName(uniqueName.str());
						tiles.push_back(curTile);
					}
					curGroup = new menu::TileGroup(groupName, tiles);
					groups.push_back(curGroup);

				} else {
					logMessage(reader.getFormattedErrorMessages());
				}

			}
		}
	}

	return groups;
}

std::vector<Tile*> JsonProcessor::loadMap(std::string saveFile) {
	Json::Reader reader;
	Json::Value mapRoot;

	std::ifstream ifile;

	Tile* loadedTile;
	utils::MapTexture* texture;
	std::vector<Tile*> loadedMap;

	std::string tileName;
	int x;
	int y;

	ifile.open(saveFile.c_str());
	if (ifile) {
		if (reader.parse(ifile, mapRoot)) {
			if (mapRoot["version"].asString().compare("v0.1") == 0) {
				Json::Value tiles = mapRoot["map"];
				for (Json::Value tile : tiles) {
					texture = NULL; // clear it
					tileName = tile["name"].asString();
					for (utils::MapTexture* curTex : utils::MapTexture::loadedTextures) {
						if (curTex->getUniqueName()->compare(tileName) == 0) {
							texture = curTex;
							break;
						}
					}
					x = tile["x"].asInt();
					y = tile["y"].asInt();
					if (texture != NULL) {
						loadedTile = new Tile(x, y, texture);
						loadedMap.push_back(loadedTile);
					} else {
						logMessage("Failed to find tile");
					}

				}
			}
		} else {
			logMessage(reader.getFormattedErrorMessages());
		}
	}

	return loadedMap;
}

std::string JsonProcessor::saveMap(std::vector<Tile*>* map) {
	Json::Value root;
	Json::StyledWriter writer;

	root["name"] = "testSave";
	root["version"] = "v0.1";

	Tile* tile;
	for (size_t i = 0; i < map->size(); i++) {
		tile = map->at(i);

		root["map"][i]["name"] = *tile->texture->getUniqueName();
		root["map"][i]["x"] = tile->x;
		root["map"][i]["y"] = tile->y;
	}

	return writer.write(root);
}

} /* namespace menu */
