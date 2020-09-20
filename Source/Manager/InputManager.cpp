/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: InputManager.cpp
Purpose: Handling input
Language: C/C++ using Visual Studio 2019
Platform: Visual Studio 2019,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
					Windows 7 SP 2

Project: 		CS529_dushyant.shukla_FinalProject_Milestone1

Author: Name: Dushyant Shukla ;  Login: dushyant.shukla  ; Student ID : 60000519
Creation date: October 16, 2019.
- End Header --------------------------------------------------------*/

#include "InputManager.h"

#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "GameObject.h"
#include "FireBullet.h"

#include "GameStateManager.h"
#include "GameState.h"

#include <memory.h>
#include <stdio.h>

extern GLFWwindow* window;
extern GameObject* player;

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

InputManager::InputManager() {
	glfwSetKeyCallback(window, KeyCallBack);
};

InputManager::~InputManager() {
}

void InputManager::Update() {
}

bool InputManager::IsKeyPressed(unsigned int keyScanCode) {
	return glfwGetKey(window, keyScanCode) == GLFW_PRESS;
}

bool InputManager::IsKeyTriggered(unsigned int keyScanCode) {
	return false;
}

bool InputManager::IsKeyReleased(unsigned int keyScanCode) {
	return glfwGetKey(window, keyScanCode) == GLFW_RELEASE;
}

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		if (GetCurrentGameState() == GAME_STATE::GAME_ACTIVE) {
			SetRender(true);
			SetNextGameState(GAME_STATE::GAME_INIT);
		}
		else {
			glfwSetWindowShouldClose(window, true);
		}
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		RenderManager::useTexture = !RenderManager::useTexture;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		RenderManager::debug = !RenderManager::debug;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (GetCurrentGameState() == GAME_STATE::GAME_ACTIVE) {
			FireBullet* pFireBullet = static_cast<FireBullet*>(player->GetComponent(COMPONENT_TYPE::COMPONENT_FIRE_BULLET));
			pFireBullet->Fire();
		}
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		if (GetCurrentGameState() == GAME_STATE::GAME_INIT) {
			RenderManager::screenIndex = 0;
			SetNextGameState(GAME_STATE::GAME_ACTIVE);
		}
	}
}