/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ObjectFactory.cpp
Purpose: creates new game objects and assigns serialized properties to them.
Language: C/C++ using Visual Studio 2019
Platform: Visual Studio 2019,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
					Windows 7 SP 2

Project: 		CS529_dushyant.shukla_FinalProject_Milestone2

Author: Name: Dushyant Shukla ;  Login: dushyant.shukla  ; Student ID : 60000519
Creation date: October 16, 2019.
- End Header --------------------------------------------------------*/

#include <memory.h>
#include <string>
#include <json.h>
#include <iostream>
#include <fstream>

#include "ObjectFactory.h"
#include "GameObject.h"
#include "Component.h"
#include "GameObjectManager.h"
#include "Transform.h"
#include "GameObjectUtility.h"

extern GameObjectManager* gameObjectManager;
extern GameObject* player;

ObjectFactory::ObjectFactory() {
}

ObjectFactory::~ObjectFactory() {
}

/*
	Pass filename as path from
*/
GameObject* ObjectFactory::LoadObject(std::string filename) {
	GameObject* newGameObject = new GameObject();
	Json::Value root;
	std::ifstream file(filename, std::ifstream::binary);
	file >> root;
	////std::cout << std::endl << "object json loaded:\n" << root << std::endl;

	std::string type = root["archetype"].asString();
	if (type._Equal("player")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::PLAYER);
	}
	else if (type._Equal("enemy-red")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL);
	}
	else if (type._Equal("enemy-turret")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::ENEMY_TURRET);
	}
	else if (type._Equal("enemy-jump")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP);
	}
	else if (type._Equal("bullet")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::BULLET);
	}
	else if (type._Equal("missile")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::MISSILE);
	}
	else if (type._Equal("start-screen-player")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::PLAYER_START_SCREEN);
	}
	else if (type._Equal("home")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::HOME);
	}
	else if (type._Equal("victory-screen-player")) {
		newGameObject->SetType(GameObjectUtility::OBJECT_TYPE::PLAYER_VICTORY_SCREEN);
	}

	Json::Value components = root["components"];

	for (int i = 0; i < components.size(); ++i) {
		Json::Value componentData = components[i];
		std::string name = componentData["component"].asString();

		Component* pNewComponent = nullptr;

		if (name._Equal("Transform")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
		}
		else if (name._Equal("Sprite")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
		}
		else if (name._Equal("UpDown")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_UP_DOWN);
		}
		else if (name._Equal("Controller")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_CONTROLLER);
		}
		else if (name._Equal("Body")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_BODY);
		}
		else if (name._Equal("Patroling")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_PATROLING);
		}
		else if (name._Equal("Jumping")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_JUMPING);
		}
		else if (name._Equal("Timed-Missile")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_TIMED_MISSILE);
		}
		else if (name._Equal("Boundary")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_BOUNDARY);
		}
		else if (name._Equal("Fire-Bullet")) {
			pNewComponent = newGameObject->AddComponent(COMPONENT_TYPE::COMPONENT_FIRE_BULLET);
		}

		if (nullptr != pNewComponent) {
			pNewComponent->Serialize(componentData);
		}
	}

	if (type._Equal("player")) {
		player = newGameObject;
	}
	gameObjectManager->AddGameObject(newGameObject);

	return newGameObject;
}

void ObjectFactory::LoadLevel(std::string filename) {
	Json::Value root;
	std::ifstream file(filename, std::ifstream::binary);
	file >> root;
	////std::cout << std::endl << "level json loaded:\n" << root << std::endl;
	for (int i = 0; i < root["entities"].size(); ++i) {
		GameObject* newGameObject = LoadObject(root["entities"][i]["file"].asString());
		Json::Value components = root["entities"][i]["components"];
		for (int j = 0; j < components.size(); ++j) {
			newGameObject->Serialize(components[j]);
		}
		newGameObject->Intialize();
	}
}