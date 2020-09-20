/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Purpose: Maintains game states
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

#include <GLFW/glfw3.h>
#include <iostream>

#include "GameStateManager.h"
#include "GameState.h"

#include "GameStatePlay.h"
#include "GameStateStart.h"

#include "InputManager.h"
#include "FrameRateController.h"
#include "LevelManager.h"
#include "ShaderProgram.h"

#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "ObjectFactory.h"


#define FRAME_RATE 60

static GAME_STATE initialGameState;
static GAME_STATE currentGameState;
static GAME_STATE previousGameState;
static GAME_STATE nextGameState;

static bool render = true;

void(*LoadGameState) ();
void(*InitializeGameState) ();
void(*UpdateGameState) (float frameTime);
void(*DrawGameState) ();
void(*FreeGameState) ();
void(*UnloadGameState) ();

extern GLFWwindow* window;

InputManager* inputManager;
FrameRateController* frameRateController;
ResourceManager* resourceManager;
GameObjectManager* gameObjectManager;
ObjectFactory* objectFactory;
PhysicsManager* physicsManager;
CollisionManager* collisionManager;
EventManager* eventManager;
RenderManager* renderManager;
ShaderProgram* shaderProgram;
LevelManager* levelManager;
GameObject* player;

void InitializeGameStateManager(GAME_STATE gameState) {
	
	currentGameState = previousGameState = nextGameState = initialGameState = gameState;

	inputManager = new InputManager();
	frameRateController = new FrameRateController(FRAME_RATE);
	shaderProgram = LoadShaderProgram("./Shaders/shader.vert", "./Shaders/shader.frag");
	renderManager = new RenderManager(shaderProgram);
	resourceManager = new ResourceManager();
	gameObjectManager = new GameObjectManager();
	objectFactory = new ObjectFactory();
	physicsManager = new PhysicsManager();
	collisionManager = new CollisionManager();
	eventManager = new EventManager();
	levelManager = new LevelManager();

	UpdateGameStateManager();

}

void UpdateGameStateManager() {

	if (currentGameState == GAME_STATE::GAME_RESTART || currentGameState == GAME_STATE::GAME_EXIT) {
		return;
	}

	switch (currentGameState) {

	case GAME_STATE::GAME_INIT:
		// load main screen 
		LoadGameState = LoadStartGameState;
		InitializeGameState = InitializeStartGameState;
		UpdateGameState = UpdateStartGameState;
		DrawGameState = DrawStartGameState;
		FreeGameState = FreeStartGameState;
		UnloadGameState = UnloadStartGameState;
		break;
		
	case GAME_STATE::GAME_ACTIVE:
		LoadGameState = LoadPlayGameState;
		InitializeGameState = InitializePlayGameState;
		UpdateGameState = UpdatePlayGameState;
		DrawGameState = DrawPlayGameState;
		FreeGameState = FreePlayGameState;
		UnloadGameState = UnloadPlayGameState;
		break;

	}
}

void MainGameLoop() {

	while (currentGameState != GAME_STATE::GAME_EXIT) {	
	
		if (currentGameState != GAME_STATE::GAME_RESTART) {
			UpdateGameStateManager();
			Reload();
		}
		else {
			nextGameState = currentGameState = previousGameState;
		}

		InitializeGameState();

		while (currentGameState == nextGameState) {
			frameRateController->FrameStart();
			float frameTime = frameRateController->GetFrameTime() / 1000.0f;

			inputManager->Update();
			if (render) {
				UpdateGameState(frameTime);
				DrawGameState();
				glfwSwapBuffers(window);
				

				if (glfwWindowShouldClose(window)) {
					nextGameState = GAME_STATE::GAME_EXIT;
				}
			}
			glfwPollEvents();
			frameRateController->FrameEnd();
		}

		FreeGameState();

		if (nextGameState != GAME_STATE::GAME_RESTART) {
			CleanUp();
		}

		previousGameState = currentGameState;
		currentGameState = nextGameState;
	}
}

GAME_STATE GetCurrentGameState() {
	return currentGameState;
}

void SetNextGameState(GAME_STATE state) {
	nextGameState = state;
}

void Reload() {
	glfwSetWindowTitle(window, u8"CONTROLS: USE ARROW KEYS TO MOVE LEFT, RIGHT & JUMP, & SPACE TO SHOOT");
	inputManager = new InputManager();
	frameRateController = new FrameRateController(FRAME_RATE);
	shaderProgram = LoadShaderProgram("./Shaders/shader.vert", "./Shaders/shader.frag");
	renderManager = new RenderManager(shaderProgram);
	resourceManager = new ResourceManager();
	gameObjectManager = new GameObjectManager();
	objectFactory = new ObjectFactory();
	physicsManager = new PhysicsManager();
	collisionManager = new CollisionManager();
	eventManager = new EventManager();
	levelManager = new LevelManager();
}

void CleanUp() {
	delete inputManager;
	delete frameRateController;
	delete resourceManager;
	delete gameObjectManager;
	delete objectFactory;
	delete physicsManager;
	delete collisionManager;
	delete eventManager;
	delete renderManager;
	delete shaderProgram;
	delete levelManager;
	player = nullptr;
}

void SetRender(bool value) {
	render = value;
}