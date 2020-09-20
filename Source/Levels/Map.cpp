/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Map.cpp
Purpose: Skeleton for Level Map class
Language: C/C++ using Visual Studio 2019
Platform: Visual Studio 2019,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
					Windows 7 SP 2

Project: 		CS529_dushyant.shukla_FinalProject

Author: Name: Dushyant Shukla ;  Login: dushyant.shukla  ; Student ID : 60000519
Creation date: December 05, 2019.
- End Header --------------------------------------------------------*/

#include "Map.h"
#include "Body.h"

#include <stdlib.h>
#include <iostream>
#include "RenderManager.h"
#include "GameStateManager.h"

Map::Map() : /*mTiles(), */mPosition(0.0f) {
}

Map::~Map() {
}

const glm::vec3& Map::GetPosition() {
	return mPosition;
}

glm::ivec3 Map::GetMapTileCoordinatesByWorldPosition(glm::vec3 worldPosition) {
	glm::ivec3 tilePosition(0);
	tilePosition.x = floor((worldPosition.x - mPosition.x) / (float)(TILE_SIZE));
	tilePosition.y = floor((worldPosition.y - mPosition.y) / (float)(TILE_SIZE));
	return tilePosition;
	// do i need to account for the center of the tile by adding TILE_SIZE / 2.0 to the numerator above
	// (int)((worldPosition.x - mPosition.x + (TILE_SIZE / 2.0)) / (float)(TILE_SIZE));
}

int Map::GetMapTileXCoordinateByWorldPosition(glm::vec3 worldPosition) {
	return (int)((worldPosition.x - mPosition.x) / (float)(TILE_SIZE));
}

int Map::GetMapTileYCoordinateByWorldPosition(glm::vec3 worldPosition) {
	return (int)((worldPosition.y - mPosition.y) / (float)(TILE_SIZE));
}

glm::vec3 Map::GetWorldPositionByTileCoordinates(glm::ivec3 tileCoordinates) {
	glm::vec3 worldPosition(0.0f);
	worldPosition.x = (float)(tileCoordinates.x * TILE_SIZE) + mPosition.x;
	worldPosition.y = (float)(tileCoordinates.y * TILE_SIZE) + mPosition.y;
	return worldPosition;
}

glm::vec3 Map::GetWorldPositionByTileCoordinates(int tileX, int tileY) {
	glm::vec3 worldPosition(0.0f);
	worldPosition.x = (float)(tileX * TILE_SIZE) + mPosition.x;
	worldPosition.y = (float)(tileY * TILE_SIZE) + mPosition.y;
	return worldPosition;
}

TILE_TYPE Map::GetTile(int tileX, int tileY) {
	if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT) {
		return TILE_TYPE::BLOCK;
	}

	return mTiles[tileY][tileX];
}

bool Map::IsTileObstacle(int tileX, int tileY, GameObjectUtility::OBJECT_TYPE objectType) {
	if ((tileX < 0 /*|| tileX == (MAP_WIDTH - 1)*/) || (tileY < 0 || tileY >= MAP_HEIGHT)) { // add - 1
		return true;
	}
	////std::cout << "tile y: " << tileY << "	tile x: " << tileX << std::endl;
	if (objectType == GameObjectUtility::OBJECT_TYPE::MISSILE || objectType == GameObjectUtility::OBJECT_TYPE::BULLET) {
		return false;
	}

	if (objectType == GameObjectUtility::OBJECT_TYPE::PLAYER) {
		if (mTiles[tileY][tileX] == TILE_TYPE::WATER) {
			RenderManager::screenIndex = 2;
			SetNextGameState(GAME_STATE::GAME_INIT);
		}

		return mTiles[tileY][tileX] == TILE_TYPE::BLOCK;
	}

	return mTiles[tileY][tileX] == TILE_TYPE::BLOCK || mTiles[tileY][tileX] == TILE_TYPE::INVISIBLE_BLOCK;
}

bool Map::IsTileGround(int tileX, int tileY) {
	if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT) {
		return false;
	}
	return mTiles[tileY][tileX] == TILE_TYPE::BLOCK;
}

bool Map::IsTileDestructibleBlock(int tileX, int tileY) {
	return false; // to be implemented later
}

bool Map::IsTileDestructible(int tileX, int tileY) {
	return false; // to be implemeneted later
}

bool Map::IsTileEmpty(int tileX, int tileY) {
	if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT) {
		return false;
	}
	return mTiles[tileY][tileX] == TILE_TYPE::EMPTY;
}

void Map::BuilMap() {
}