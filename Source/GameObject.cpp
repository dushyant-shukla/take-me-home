/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Purpose: Container of Gameobjects
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

#include "GameObject.h"

#include "Sprite.h"
#include "Transform.h"
#include "UpDown.h"
#include "Controller.h"
#include "Component.h"
#include "Body.h"
#include "Patroling.h"
#include "Jumping.h"
#include "TimedMissile.h"
#include "Boundary.h"
#include "FireBullet.h"

GameObject::GameObject() :mIsActive(true) {
}

GameObject::~GameObject() {
	for (auto component : mComponents) {
		if (component->GetType() == COMPONENT_TYPE::COMPONENT_BODY) {
			int a = 10;
			int b = a + 1;
		}
		delete component;
	}
}

void GameObject::Update() {
	/*if (type == GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP) {
		//std::cout << "";
	}*/

	for (auto component : mComponents) {
		COMPONENT_TYPE type = component->GetType();
		if (type == COMPONENT_TYPE::COMPONENT_JUMPING) {
			//std::cout << "";
		}
		switch (type)
		{
		case COMPONENT_TYPE::COMPONENT_TRANSFORM:
			(static_cast<Transform*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_SPRITE:
			(static_cast<Sprite*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_UP_DOWN:
			(static_cast<UpDown*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_CONTROLLER:
			(static_cast<Controller*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_BODY:
			(static_cast<Body*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_PATROLING:
			(static_cast<Patroling*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_JUMPING:
			(static_cast<Jumping*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_TIMED_MISSILE:
			(static_cast<TimedMissile*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_BOUNDARY:
			(static_cast<Boundary*> (component))->Update();
			break;
		case COMPONENT_TYPE::COMPONENT_FIRE_BULLET:
			(static_cast<FireBullet*> (component))->Update();
			break;
		}
	}
}

Component* GameObject::GetComponent(COMPONENT_TYPE type) {
	for (auto component : mComponents) {
		if (component->GetType() == type) {
			return component;
		}
	}
	return nullptr;
}

Component* GameObject::AddComponent(COMPONENT_TYPE type) {
	Component* pComponent = GetComponent(type);

	if (nullptr != pComponent) {
		return pComponent;
	}

	switch (type) {
	case COMPONENT_TYPE::COMPONENT_SPRITE:
		pComponent = new Sprite();
		break;

	case COMPONENT_TYPE::COMPONENT_TRANSFORM:
		pComponent = new Transform();
		break;

	case COMPONENT_TYPE::COMPONENT_UP_DOWN:
		pComponent = new UpDown();
		break;

	case COMPONENT_TYPE::COMPONENT_CONTROLLER:
		pComponent = new Controller();
		break;

	case COMPONENT_TYPE::COMPONENT_BODY:
		pComponent = new Body();
		break;

	case COMPONENT_TYPE::COMPONENT_PATROLING:
		pComponent = new Patroling();
		break;

	case COMPONENT_TYPE::COMPONENT_JUMPING:
		pComponent = new Jumping();
		break;

	case COMPONENT_TYPE::COMPONENT_TIMED_MISSILE:
		pComponent = new TimedMissile();
		break;

	case COMPONENT_TYPE::COMPONENT_BOUNDARY:
		pComponent = new Boundary();
		break;
	case COMPONENT_TYPE::COMPONENT_FIRE_BULLET:
		pComponent = new FireBullet();
		break;
	}

	pComponent->SetOwner(this);
	mComponents.push_back(pComponent);
	return pComponent;
}

void GameObject::Intialize() {
	for (auto component : mComponents) {
		component->Initialize();
	}
}

void GameObject::HandleEvent(Event* pEvent) {
	GameObjectUtility::OBJECT_TYPE type = this->GetType();

	for (auto component : mComponents) {
		component->HandleEvent(pEvent);
	}
}

void GameObject::Serialize(Json::Value componentData) {
	std::string componentName = componentData["component"].asString();
	Component* component = nullptr;

	if (componentName._Equal("Transform")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM);
	}
	else if (componentName._Equal("Sprite")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE);
	}
	else if (componentName._Equal("UpDown")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_UP_DOWN);
	}
	else if (componentName._Equal("Controller")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_CONTROLLER);
	}
	else if (componentName._Equal("Body")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_BODY);
	}
	else if (componentName._Equal("Patroling")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_PATROLING);
	}
	else if (componentName._Equal("Jumping")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_JUMPING);
	}
	else if (componentName._Equal("Missile-Launch")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_TIMED_MISSILE);
	}
	else if (componentName._Equal("Boundary")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_BOUNDARY);
	}
	else if (componentName._Equal("Fire-Bullet")) {
		component = GetComponent(COMPONENT_TYPE::COMPONENT_FIRE_BULLET);
	}

	component->Serialize(componentData);
}

GameObjectUtility::OBJECT_TYPE GameObject::GetType() {
	return type;
}

void GameObject::SetType(GameObjectUtility::OBJECT_TYPE value) {
	type = value;
}

bool GameObject::GetIsActive() {
	return mIsActive;
}

void GameObject::SetIsActive(bool value) {
	mIsActive = value;
}