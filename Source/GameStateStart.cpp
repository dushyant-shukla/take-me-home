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




void LoadStartGameState() {
}

void InitializeStartGameState() {
	//objectFactory->LoadLevel("./Assets/levels/victory-screen.json");
	//objectFactory->LoadLevel("./Assets/levels/game-start-screen.json");
	//objectFactory->LoadLevel("./Assets/levels/game-over-screen.json");
	if (RenderManager::screenIndex == 0) {
		objectFactory->LoadLevel("./Assets/levels/game-start-screen.json");
	}
	else if (RenderManager::screenIndex == 1) {
		objectFactory->LoadLevel("./Assets/levels/victory-screen.json");
	}
	else if (RenderManager::screenIndex == 2) {
		objectFactory->LoadLevel("./Assets/levels/game-over-screen.json");
	}
}

void UpdateStartGameState(float frameTime) {
}

void DrawStartGameState() {
	glClearColor(0.863f, 0.863f, 0.863f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderManager->Draw(shaderProgram, gameObjectManager->GetGameObjects());
}

void FreeStartGameState() {
	//gameObjectManager->Clear();
}

void UnloadStartGameState() {
}