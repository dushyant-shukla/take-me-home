#include "GameStateStart.h"

#include <glad/glad.h>

#include "ShaderProgram.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectFactory.h"
#include "GameObjectManager.h"

extern ResourceManager* resourceManager;
extern RenderManager* renderManager;
extern ShaderProgram* shaderProgram;
extern ObjectFactory* objectFactory;
extern GameObjectManager* gameObjectManager;

void LoadVictoryGameState() {
}

void InitializeVictoryGameState() {
	//objectFactory->LoadLevel("./Assets/levels/game-victory-screen.json");
	objectFactory->LoadLevel("./Assets/levels/game-start-screen.json");
}

void UpdateVictoryGameState(float frameTime) {
}

void DrawVictoryGameState() {
	glClearColor(0.863f, 0.863f, 0.863f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderManager->Draw(shaderProgram, gameObjectManager->GetGameObjects());
}

void FreeVictoryGameState() {
	//gameObjectManager->Clear();
}

void UnloadVictoryGameState() {
}