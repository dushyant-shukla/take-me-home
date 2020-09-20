/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EventManager.h
Purpose: Skeleton for EventManager.cpp
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

#pragma once
#include "Component.h"
#include <list>
#include <unordered_map>
class GameObject;

enum class EVENT_TYPE {
	COLLIDE,
	PLAYER_HIT,
	LAUNCH_MISSILE,
	NUM
};

class Event {
	public:
	Event(EVENT_TYPE Type);
	virtual ~Event() {}

	EVENT_TYPE mEventType;
	float mTimer;
	float mTimerMax;
};

class EventManager {
	public:
	EventManager();
	~EventManager();

	void BroadCastEvent(Event* pEvent);
	void BroadCastEventToSubscribers(Event* pEvent);
	void AddTimedEvent(Event* pEvent);

	void Update(float FrameTime);
	void Subscribe(EVENT_TYPE Et, GameObject* pGO);

	std::list<Event*> mEvents;
	std::unordered_map<EVENT_TYPE, std::list<GameObject*>> mSubscriptions;
};


class CollisionEvent : public Event {

	public:
	CollisionEvent();
	~CollisionEvent();

	GameObject* mpObject1;
	GameObject* mpObject2;
};