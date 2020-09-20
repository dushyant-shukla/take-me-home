#pragma once

#include <vector>
#include <map>

#include "TileType.h"

class Map;
class Texture2D;

class LevelManager {

public:
	LevelManager();
	~LevelManager();

	Map* GetActiveMap();
	void LoadMap();
	void DrawActiveLevel();

private:
	std::vector<Map*> mSavedMaps;
	Map* mActiveMap;
	std::map<TILE_TYPE, Texture2D*> mMapTextures;

};
