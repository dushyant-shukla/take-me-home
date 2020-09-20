#include "LevelMap.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "ShaderProgram.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

extern ResourceManager* resourceManager;
extern RenderManager* renderManager;
extern ShaderProgram* shaderProgram;

LevelMap::LevelMap() {
	brick = resourceManager->LoadTexture("./Assets/brick-wall-brown.png");
	LoadLevelMap(0, 25);
}

LevelMap::~LevelMap() {
}

void LevelMap::LoadLevelMap(int rows, int columns) {
	for (int row = 0; row < rows; ++row) {
		for (int column = 0; column < columns; ++column) {
			map[row][column] = *(*(level + row) + column);
		}
	}
}

void LevelMap::DrawLevelMap(int rows, int columns) {
	int type = 0;
	glm::vec3 scaleVector = glm::vec3(32.0f, 32.0f, 1.0f);

	for (int row = 0; row < rows; ++row) {
		for (int column = 0; column < columns; ++column) {
			type = *(*(map + row) + column);
			switch (type) {
			case 0:
				/*std::cout << "TRANSFORMATION MATRIX" << std::endl;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						std::cout << transform[i][j] << "\t";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
				std::cout << std::endl;*/
				
				break;
			case 1:
				if (row * 32 > 640) {
					std::cout << "exceeded height of viewport" << std::endl;
				}
				if (column * 32 > 800) {
					std::cout << "exceeded width of viewport" << std::endl;
				}
				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(column * 32, row * 32, 0.0f));
				transform = glm::scale(transform, scaleVector);
				renderManager->DrawTexture(shaderProgram, brick, transform);
				break;
			default:
				break;
			}
		}
	}
}