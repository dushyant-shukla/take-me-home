/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Jumping.cpp
Purpose: Jumping component
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

#include "Jumping.h"
#include "Body.h"
#include "GameObject.h"

Jumping::Jumping() : Component(COMPONENT_TYPE::COMPONENT_JUMPING) {
}

Jumping::~Jumping() {
}

void Jumping::Update() {
	Body* pBody = static_cast<Body*> (GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
	if (pBody->GetIsOnGround()) {
		glm::vec3 velocity = pBody->GetVelocity();
		velocity.y = mJumpSpeed;
		pBody->SetVelocity(velocity);
		pBody->SetIsOnGround(false);
		pBody->SetStateToJumping();
	}
}

void Jumping::Serialize(Json::Value value) {
	if (value["jump-speed"] != Json::nullValue) {
		mJumpSpeed = value["jump-speed"].asFloat();
	}
}

void Jumping::Initialize() {
	Body* pBody = static_cast<Body*> (GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
	pBody->SetIsOnGround(true);
}

void Jumping::HandleEvent(Event* pEvent) {
}

float Jumping::GetJumpSpeed() {
	return mJumpSpeed;
}

void Jumping::UpdateJumpSpeed(float value) {
	if (std::abs(mJumpSpeed) < 160) {
		mJumpSpeed = -160;
	}
	else {
		mJumpSpeed += value;
	}
}