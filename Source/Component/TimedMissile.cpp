/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TimedMissile.cpp
Purpose: TimedMissile component
Language: C/C++ using Visual Studio 2019
Platform: Visual Studio 2019,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
					Windows 7 SP 2

Project: 		CS529_dushyant.shukla_FinalProject

Author: Name: Dushyant Shukla ;  Login: dushyant.shukla  ; Student ID : 60000519
Creation date: December 05, 2019.
- End Header --------------------------------------------------------*/

#include "TimedMissile.h"
#include "EventManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Body.h"
#include "Boundary.h"
#include "TileType.h"

#include <iostream>

extern EventManager* eventManager;
extern GameObjectManager* gameObjectManager;
extern ObjectFactory* objectFactory;
extern GameObject* player;

TimedMissile::TimedMissile() : Component(COMPONENT_TYPE::COMPONENT_TIMED_MISSILE), mTimer(0.0f) {
}

TimedMissile::~TimedMissile() {
}

void TimedMissile::Update() {
}

void TimedMissile::Serialize(Json::Value componentData) {
	if (componentData["timer"] != Json::nullValue) {
		mTimer = componentData["timer"].asFloat();
	}
	if (componentData["missile-archetype-file"] != Json::nullValue) {
		archeTypeFile = componentData["missile-archetype-file"].asString();
	}
	if (componentData["missile-speed"] != Json::nullValue) {
		missileSpeed = componentData["missile-speed"].asFloat();
	}
}

void TimedMissile::Initialize() {
	Event* event = new Event(EVENT_TYPE::LAUNCH_MISSILE);
	event->mTimerMax = mTimer;
	event->mTimer = mTimer;
	eventManager->AddTimedEvent(event);
	eventManager->Subscribe(EVENT_TYPE::LAUNCH_MISSILE, this->GetOwner());
}

void TimedMissile::HandleEvent(Event* pEvent) {
	//Later I can implement it using update() of this component instead of event manager
	if (pEvent->mEventType == EVENT_TYPE::LAUNCH_MISSILE && pEvent->mTimerMax == mTimer) {
		// handle the event
		//std::cout << "\n|||||||||>>>>>>" << std::endl;
		GameObject* missile = objectFactory->LoadObject(archeTypeFile);
		missile->SetType(GameObjectUtility::OBJECT_TYPE::MISSILE);
		Body* pBody = static_cast<Body*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
		Transform* pTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		glm::vec3 scale = pTransform->GetScale();

		Transform* missileTransform = static_cast<Transform*>(missile->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		Body* pBodyMissile = static_cast<Body*>(missile->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
		Boundary* missileBoundary = static_cast<Boundary*>(missile->GetComponent(COMPONENT_TYPE::COMPONENT_BOUNDARY));
		float velocityX;
		if ((static_cast<Body*> (player->GetComponent(COMPONENT_TYPE::COMPONENT_BODY)))->GetPosition().x - pBody->GetPosition().x > 0.0f) {
			glm::vec3 position = glm::vec3(pBody->GetPosition().x + scale.x, pBody->GetPosition().y + scale.y / 8, 0.0);
			missileTransform->SetPosition(position.x, position.y);
			missileBoundary->SetStartPosition(position);
			missileBoundary->SetDistance(MAP_WIDTH * TILE_SIZE);
			pBodyMissile->SetVelocity(missileSpeed, 0);
		}
		else {
			glm::vec3 position = glm::vec3(pBody->GetPosition().x - missileTransform->GetScale().x, pBody->GetPosition().y + scale.y / 8, 0.0);
			missileTransform->SetPosition(position.x, position.y);
			missileBoundary->SetStartPosition(position);
			missileBoundary->SetDistance(MAP_WIDTH * TILE_SIZE);
			pBodyMissile->SetVelocity(-missileSpeed, 0);
		}

		pBodyMissile->Initialize();
	}
}