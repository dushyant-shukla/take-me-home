/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LevelManager.cpp
Purpose: Generates and maintains levels in game
Language: C/C++ using Visual Studio 2019
Platform: Visual Studio 2019,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
					Windows 7 SP 2

Project: 		CS529_dushyant.shukla_FinalProject_Milestone3

Author: Name: Dushyant Shukla ;  Login: dushyant.shukla  ; Student ID : 60000519
Creation date: November 10, 2019.
- End Header --------------------------------------------------------*/

#include "LevelManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "ShaderProgram.h"
#include "Map.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

extern ResourceManager* resourceManager;
extern RenderManager* renderManager;
extern ShaderProgram* shaderProgram;

LevelManager::LevelManager() : mSavedMaps(), mActiveMap(nullptr), mMapTextures() {
	Texture2D* block = resourceManager->LoadTexture("./Assets/block-grey-small.png", true);
	Texture2D* cloud1 = resourceManager->LoadTexture("./Assets/cloud-pattern-1.png", true);
	Texture2D* cloud2 = resourceManager->LoadTexture("./Assets/cloud-pattern-2.png", true);
	Texture2D* cloud3 = resourceManager->LoadTexture("./Assets/cloud-pattern-3.png", true);
	Texture2D* water = resourceManager->LoadTexture("./Assets/water.png", true);
	mMapTextures[TILE_TYPE::BLOCK] = block;
	mMapTextures[TILE_TYPE::CLOUD_1] = cloud1;
	mMapTextures[TILE_TYPE::CLOUD_2] = cloud2;
	mMapTextures[TILE_TYPE::CLOUD_3] = cloud3;
	mMapTextures[TILE_TYPE::WATER] = water;

	Map* map1 = new Map();
	mSavedMaps.push_back(map1);

	mActiveMap = map1;
}

LevelManager::~LevelManager() {
}

Map* LevelManager::GetActiveMap() {
	return mActiveMap;
}

void LevelManager::LoadMap() {
}

void LevelManager::DrawActiveLevel() {
	TILE_TYPE type;

	glm::vec3 scaleVector = glm::vec3(32.0f, 32.0f, 1.0f);

	for (int row = 0; row < MAP_HEIGHT; ++row) {
		for (int column = 0; column < MAP_WIDTH; ++column) {
			type = *(*(mActiveMap->mTiles + row) + column);
			switch (type) {
			case TILE_TYPE::EMPTY:
				/*//std::cout << "TRANSFORMATION MATRIX" << std::endl;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						//std::cout << transform[i][j] << "\t";
					}
					//std::cout << std::endl;
				}
				//std::cout << std::endl;
				//std::cout << std::endl;*/

				break;
			case TILE_TYPE::BLOCK:
			case TILE_TYPE::CLOUD_1:
			case TILE_TYPE::CLOUD_2:
			case TILE_TYPE::CLOUD_3:
			case TILE_TYPE::WATER:
				/*if (row * 32 > 600) {
					//std::cout << "exceeded height of viewport" << std::endl;
				}
				if (column * 32 > 1000) {
					//std::cout << "exceeded width of viewport" << std::endl;
				}*/
				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(column * 32, row * 32, 0.0f));
				transform = glm::scale(transform, scaleVector);
				renderManager->DrawTexture(shaderProgram, mMapTextures[type], transform);
				break;
			default:
				break;
			}
		}
	}
}