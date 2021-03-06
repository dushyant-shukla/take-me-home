/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateController.cpp
Purpose: Managing frames per second in the game
Language: C/C++ using Visual Studio 2019
Platform: Visual Studio 2019,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
					Windows 7 SP 2

Project: 		CS529_dushyant.shukla_FinalProject_Milestone1

Author: Name: Dushyant Shukla ;  Login: dushyant.shukla  ; Student ID : 60000519
Creation date: October 16, 2019.
- End Header --------------------------------------------------------*/

#include <limits.h>
#include <SDL_timer.h>
#include "FrameRateController.h"
#include <stdio.h>

FrameRateController::FrameRateController(unsigned int maxFrameRate) {
	
	if (0 == maxFrameRate) {
		maxFrameRate = UINT_MAX;
	}

	mMaxFrameRate = maxFrameRate;

	mTicksPerFrame = 1000 / mMaxFrameRate;

	mTickStart = 0;

	mTickEnd = 0;

	mFrameTime = 0;

}


FrameRateController::~FrameRateController() {
}


void FrameRateController::FrameStart() {
	mTickStart = SDL_GetTicks();
}


void FrameRateController::FrameEnd() {

	mTickEnd = SDL_GetTicks();
	
	while ((mTickEnd - mTickStart) < mTicksPerFrame) {
		mTickEnd = SDL_GetTicks();
	}

	mFrameTime = mTickEnd - mTickStart;
	if (mFrameTime >= 16) {
		mFrameTime = 16;
	}
}

unsigned int FrameRateController::GetFrameTime() {
	return mFrameTime;
}