/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Controller.cpp
Purpose:  Controller component for enabling input
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

#include "RenderManager.h"
#include "Controller.h"
#include "Transform.h"
#include "Body.h"
#include "InputManager.h"
#include "GameObject.h"
#include "FireBullet.h"

#include <iostream>

#define FORCE_X			100.0
#define FORCE_Y_UP		100.0
#define FORCE_Y_DOWN	20.0

extern InputManager* inputManager;

Controller::Controller() : Component(COMPONENT_TYPE::COMPONENT_CONTROLLER) {
}

Controller::~Controller() {
}

void Controller::Update() {
	Transform* pTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Body* pBody = static_cast<Body*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
	FireBullet* pFireBullet = static_cast<FireBullet*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_FIRE_BULLET));

	if (nullptr != pTransform && pBody != nullptr) {
		if (inputManager->IsKeyPressed(GLFW_KEY_UP)) {
			//pBody->UpdateTotalForce(0.0f, -FORCE_Y_UP);
			////std::cout << "CURRENT STATE:: " << mCurrentState;
			pBody->Jump();
			//pBody->MoveUp();
		}
		if (inputManager->IsKeyPressed(GLFW_KEY_RIGHT)) {
			//pBody->UpdateTotalForce(FORCE_X, 0.0f);
			pBody->MoveRight();
		}
		if (inputManager->IsKeyPressed(GLFW_KEY_DOWN)) {
			//pBody->UpdateTotalForce(0.0f, FORCE_Y_DOWN);
			//pBody->MoveDown();
		}
		if (inputManager->IsKeyPressed(GLFW_KEY_LEFT)) {
			//pBody->UpdateTotalForce(-FORCE_X, 0.0f);
			pBody->MoveLeft();
		}

		RenderManager::UpdateCamera(pTransform->GetPosition());
	}
}

void Controller::Serialize(Json::Value componentData) {
}

void Controller::Initialize() {
}

void Controller::HandleEvent(Event* pEvent) {
}