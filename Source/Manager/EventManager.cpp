/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EventManager.cpp
Purpose: Generates and maintain events in game
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
Creation date: November 10, 2019.
- End Header --------------------------------------------------------*/

#include "EventManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"

extern GameObjectManager* gameObjectManager;

Event::Event(EVENT_TYPE type) : mEventType(type), mTimer(0.0f), mTimerMax(0.0f) {
}

////////////////////////////////////////////////////////////////////

EventManager::EventManager() {
}

EventManager::~EventManager() {
}

///////////////////////////////////////////////////////////////////

CollisionEvent::CollisionEvent() : Event(EVENT_TYPE::COLLIDE), mpObject1(NULL), mpObject2(NULL) {
}

CollisionEvent::~CollisionEvent() {
}

//////////////////////////////////////////////////////////////////

void EventManager::BroadCastEvent(Event* pEvent) {
	for (GameObject* pObj : gameObjectManager->GetGameObjects()) {
		pObj->HandleEvent(pEvent);
	}
}

void EventManager::BroadCastEventToSubscribers(Event* pEvent) {
	auto& listOfSubscribers = mSubscriptions[pEvent->mEventType];
	for (auto pRegisteredGO : listOfSubscribers) {
		pRegisteredGO->HandleEvent(pEvent);
	}

	//printf("Finished broadcasting event with event-type# %d\n", pEvent->mEventType);
	//delete pEvent; // check this out
}

void EventManager::AddTimedEvent(Event* pEvent) {
	std::list<Event*>::iterator it;
	for (it = mEvents.begin(); it != mEvents.end(); ++it) {
		if ((*it)->mEventType == pEvent->mEventType && (*it)->mTimerMax == pEvent->mTimerMax) {
			return;
		}
	}
	mEvents.push_back(pEvent);
}

void EventManager::Update(float FrameTime) {
	std::list<Event*>::iterator it, itTemp;

	it = mEvents.begin();

	while (it != mEvents.end()) {
		Event* pEvent = *it;
		pEvent->mTimer -= FrameTime;

		if (pEvent->mTimer < 0.0f) {
			BroadCastEventToSubscribers(pEvent);
			pEvent->mTimer = pEvent->mTimerMax;
			/*delete pEvent;
			itTemp = it;
			++itTemp;
			mEvents.erase(it);
			it = itTemp;*/
		}
		else {
			++it;
		}
	}
}

void EventManager::Subscribe(EVENT_TYPE Et, GameObject* pGO) {
	for (auto pRegisteredGO : mSubscriptions[Et])
	{
		if (pRegisteredGO == pGO)
			return;
	}
	mSubscriptions[Et].push_back(pGO);
}