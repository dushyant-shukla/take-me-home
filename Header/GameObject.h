/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Purpose: Skeleton for Gameobject.cpp
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

#pragma once

#include <vector>
#include <json.h>

#include "GameObjectUtility.h"
#include "Component.h"

class Event;

class GameObject {

public:
	GameObject();
	~GameObject();

	void Update();
	Component* GetComponent(COMPONENT_TYPE type);
	Component* AddComponent(COMPONENT_TYPE type);

	void Intialize();

	void HandleEvent(Event* pEvent);

	void Serialize(Json::Value component);

	GameObjectUtility::OBJECT_TYPE GetType();
	void SetType(GameObjectUtility::OBJECT_TYPE value);

	bool GetIsActive();
	void SetIsActive(bool value);

private:
	std::vector <Component*> mComponents;
	GameObjectUtility::OBJECT_TYPE type;
	bool mIsActive;
};
