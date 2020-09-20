/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FireBullet.cpp
Purpose: FireBullet component
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
Creation date: December 05, 2019.
- End Header --------------------------------------------------------*/

#include "FireBullet.h"
#include "GameObject.h"
#include "Transform.h"
#include "TileType.h"
#include "ObjectFactory.h"
#include "Body.h"
#include "Boundary.h"

#include <iostream>

extern ObjectFactory* objectFactory;
extern GameObject* player;

FireBullet::FireBullet() : Component(COMPONENT_TYPE::COMPONENT_FIRE_BULLET) {
}

FireBullet::~FireBullet() {
}

void FireBullet::Update() {
}

void FireBullet::Serialize(Json::Value componentData) {
	if (componentData["bullet-archetype-file"] != Json::nullValue) {
		archeTypeFile = componentData["bullet-archetype-file"].asString();
	}
	if (componentData["bullet-speed"] != Json::nullValue) {
		bulletSpeed = componentData["bullet-speed"].asFloat();
	}
}

void FireBullet::Initialize() {
}

void FireBullet::HandleEvent(Event* pEvent) {
}

void FireBullet::Fire() {
	//std::cout << "\n====>>" << std::endl;

	GameObject* bullet = objectFactory->LoadObject(archeTypeFile);
	bullet->SetType(GameObjectUtility::OBJECT_TYPE::BULLET);
	Body* pBody = static_cast<Body*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
	Transform* pTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	glm::vec3 scale = pTransform->GetScale();

	Transform* bulletTransform = static_cast<Transform*>(bullet->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Body* bulletBody = static_cast<Body*>(bullet->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
	Boundary* bulletBoundary = static_cast<Boundary*>(bullet->GetComponent(COMPONENT_TYPE::COMPONENT_BOUNDARY));
	if (pBody->IsFacingRight()/*pBody->GetPosition().x - pBody->GetPreviousPosition().x >= 0.0f*/) {
		glm::vec3 position = glm::vec3(pBody->GetPosition().x + scale.x, pBody->GetPosition().y + scale.y / 8, 0.0);
		bulletTransform->SetPosition(position.x, position.y);
		bulletBoundary->SetStartPosition(position);
		bulletBoundary->SetDistance(350.0);
		bulletBody->SetVelocity(bulletSpeed, 0);
	}
	else {
		glm::vec3 position = glm::vec3(pBody->GetPosition().x - 1.5 * scale.x, pBody->GetPosition().y + scale.y / 8, 0.0);
		bulletTransform->SetPosition(position.x, position.y);
		bulletBoundary->SetStartPosition(position);
		bulletBoundary->SetDistance(350.0);
		bulletBody->SetVelocity(-bulletSpeed, 0);
	}

	bulletBody->Initialize();
}