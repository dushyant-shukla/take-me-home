/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Updown.cpp
Purpose : makes game objects go upand down
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

#include "FrameRateController.h"
#include "GameObject.h"

#include "./Component/UpDown.h"
#include "./Component/Transform.h"
#include "EventManager.h"
#include "./Body.h"

extern FrameRateController* frameRateController;
extern EventManager* eventManager;

UpDown::UpDown() : Component(COMPONENT_TYPE::COMPONENT_UP_DOWN), mGoingUp(false), mTimer(1000) {
}

UpDown::~UpDown() {
}

void UpDown::Update() {
	mTimer -= frameRateController->GetFrameTime();

	if (mTimer < 0) {
		mTimer = 1000;
		mGoingUp = !mGoingUp;
	}

	Transform* mpTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	if (nullptr != mpTransform) {

		if (true == mGoingUp) {
			mpTransform->UpdatePosition(0.0f, -0.25f * frameRateController->GetFrameTime()); // SDL coordinate has origin at the TOP-LEFT corner of the view port.
		}
		else {
			mpTransform->UpdatePosition(0.0f, +0.25f * frameRateController->GetFrameTime());
		}
	}

}

void UpDown::Serialize(Json::Value componentData) {
	if (componentData["going-up"] != Json::nullValue) {
		mGoingUp = componentData["going-up"].asBool();
	}

	if (componentData["timer"] != Json::nullValue) {
		mTimer = componentData["timer"].asInt();
	}
}

void UpDown::Initialize() {
	eventManager->Subscribe(EVENT_TYPE::COLLIDE, this->GetOwner());
}

void UpDown::HandleEvent(Event* pEvent) {
	if (pEvent->mEventType == EVENT_TYPE::COLLIDE)
	{
		CollisionEvent* pRealEvent = (CollisionEvent*) pEvent;
		if(pRealEvent->mpObject1 == this->GetOwner() || pRealEvent->mpObject2 == this->GetOwner()) {
			Transform* mpTransform = static_cast<Transform*>(this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
			if (mpTransform) {
				mpTransform->UpdatePosition(50.0f, 0.0f);
			}
			printf("%s", "Collison event handled!!\n");
		}
	}
}