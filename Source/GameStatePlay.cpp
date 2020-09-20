#include "GameStatePlay.h"

#include "LevelManager.h"
#include "ShaderProgram.h"

#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"

#include "GameObject.h"
#include "ObjectFactory.h"

#include "Transform.h"
#include "Sprite.h"
#include "Controller.h"
#include "UpDown.h"
#include "Body.h"

extern ResourceManager* resourceManager;
extern GameObjectManager* gameObjectManager;
extern ObjectFactory* objectFactory;
extern PhysicsManager* physicsManager;
extern EventManager* eventManager;
extern LevelManager* levelManager;
extern RenderManager* renderManager;
extern ShaderProgram* shaderProgram;

void LoadPlayGameState() {
}

// dunno what to do here
void InitializePlayGameState() {
	// may be select appropriate level etc.
	objectFactory->LoadLevel("./Assets/levels/level-1.json");
	//objectFactory->LoadLevel("./Assets/levels/level-2.json");
}

void UpdatePlayGameState(float frameTime) {
	gameObjectManager->Update();
	physicsManager->Update(frameTime);
	eventManager->Update(frameTime);
}

void DrawPlayGameState() {
	glClearColor(0.863f, 0.863f, 0.863f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	levelManager->DrawActiveLevel();

	renderManager->Draw(shaderProgram, gameObjectManager->GetGameObjects());
	if (RenderManager::debug) {
		renderManager->DebugDraw(shaderProgram, gameObjectManager->GetGameObjects());
	}
}

// free all game objects etc
void FreePlayGameState() {
	//gameObjectManager->Clear();
}

// delet all global pointers
void UnloadPlayGameState() {
}