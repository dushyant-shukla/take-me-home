#pragma once

#include "GameState.h"

extern GAME_STATE initialGameState;
extern GAME_STATE currentGameState;
extern GAME_STATE previousGameState;
extern GAME_STATE nextGameState;

//extern void(*LoadGameState) () = 0;
//extern void(*InitializeGameState) () = 0;
//extern void(*UpdateGameState) (float frameTime) = 0;
//extern void(*DrawGameState) () = 0;
//extern void(*FreeGameState) () = 0;
//extern void(*UnloadGameState) () = 0;

void InitializeGameStateManager(GAME_STATE gameState);

void UpdateGameStateManager();

void MainGameLoop();

GAME_STATE GetCurrentGameState();

void SetNextGameState(GAME_STATE state);

void CleanUp();

void Reload();

void SetRender(bool value);

