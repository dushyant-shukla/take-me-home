/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Component.h
Purpose: Skeleton for Component.cpp
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
#include <json.h>
#include "stdio.h"

class GameObject;
class Event;

enum class COMPONENT_TYPE {

	COMPONENT_TRANSFORM,
	COMPONENT_SPRITE,
	COMPONENT_CONTROLLER,
	COMPONENT_UP_DOWN,
	COMPONENT_BODY,
	COMPONENT_PATROLING,
	COMPONENT_JUMPING,
	COMPONENT_TIMED_MISSILE,
	COMPONENT_BOUNDARY,
	COMPONENT_FIRE_BULLET,
	COMPONENT_HEALTH
};


class Component {

	public:
	Component(COMPONENT_TYPE type);
	virtual ~Component();

	virtual void Update() = 0;
	virtual void Serialize(Json::Value json) = 0;
	virtual void Initialize() = 0;
	virtual void HandleEvent(Event* pEvent) = 0;

	COMPONENT_TYPE GetType() const { return mType; }
	GameObject* GetOwner() const { return mpOwner; }
	void SetOwner(GameObject* owner) { mpOwner = owner; }

	private:
	COMPONENT_TYPE mType;
	GameObject* mpOwner;
};
