/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TimedMissile.h
Purpose: Skeleton for TimedMissile component
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

#pragma once

#include "Component.h"

#include <string>

class TimedMissile : public Component {

public:
	TimedMissile();
	~TimedMissile();

	void Update();
	// in the update method 
	// take the body component and check for hitting right and left wall and reverse the velocities accordingly
	void Serialize(Json::Value json);
	void Initialize();
	void HandleEvent(Event* pEvent);

private:
	float mTimer;
	std::string archeTypeFile;
	float missileSpeed;
};
