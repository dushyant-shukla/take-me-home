/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Transform.h
Purpose: Skeleton for Transform.h
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

#include "Component.h"
//#include "Math2D.h"

#include <glm/glm.hpp>

class Transform : public Component {

	public:
	Transform();
	~Transform();

	void Update();
	void Serialize(Json::Value json);
	void Initialize();
	void HandleEvent(Event* pEvent);

	glm::vec3& GetPosition();
	void SetPosition(float x, float y);
	void UpdatePosition(float dx, float dy);

	void SetScale(float scaleX, float scaleY);
	glm::mat4& getTransform();
	glm::vec3& GetScale();

	void SetTrasform(glm::mat4 value);

	private:
	glm::vec3 mPosition;
	glm::mat4 mTransform;
	glm::vec3 mScale;
};