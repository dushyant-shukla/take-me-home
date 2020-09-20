/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Transform.cpp
Purpose: Component for placing game objects in the scene
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

#include <glm/gtc/matrix_transform.hpp>

#include "./Component/Transform.h"
#include "GameObject.h"
#include "Body.h"
#include <iostream>

Transform::Transform() : Component(COMPONENT_TYPE::COMPONENT_TRANSFORM), mPosition(0.0f), mTransform(glm::mat4(1.0f)), mScale(1.0f) {
}

Transform::~Transform() {
}

void Transform::Update() {
	/*mTransform = glm::mat4(1.0f);
	mTransform = glm::translate(mTransform, glm::vec3(round(mPosition.x), round(mPosition.y), 0.0f));
	mTransform = glm::scale(mTransform, glm::vec3(mScale.x, mScale.y, 1.0f));*/ // change this to use scale

	/*//std::cout << "TRANSFORMATION MATRIX" << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//std::cout << mTransform[i][j] << "\t";
		}
		//std::cout << std::endl;
	}

	//std::cout << std::endl;
	//std::cout << std::endl;*/
}

void Transform::UpdatePosition(float dx, float dy) {
	mPosition.x += dx;
	mPosition.y += dy;
}

void Transform::SetPosition(float x, float y) {
	mPosition.x = x;
	mPosition.y = y;
}

glm::vec3& Transform::GetPosition() {
	return mPosition;
};

void Transform::Serialize(Json::Value componentData) {
	if (componentData["pos-x"] != Json::nullValue) {
		mPosition.x = componentData["pos-x"].asFloat();
	}

	if (componentData["pos-y"] != Json::nullValue) {
		mPosition.y = componentData["pos-y"].asFloat();
	}

	if (componentData["scale-x"] != Json::nullValue) {
		mScale.x = componentData["scale-x"].asFloat();
	}

	if (componentData["scale-y"] != Json::nullValue) {
		mScale.y = componentData["scale-y"].asFloat();
	}
}

void Transform::Initialize() {
	mTransform = glm::translate(mTransform, glm::vec3(round(mPosition.x), round(mPosition.y), 0.0f));

	/*mTransform = glm::translate(mTransform, glm::vec3(0.5f * mScale.x, 0.5f * mScale.y, 0.0f));
	mTransform = glm::rotate(mTransform, 100.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	mTransform = glm::translate(mTransform, glm::vec3(-0.5f * mScale.x, -0.5f * mScale.y, 0.0f));*/

	//mTransform = glm::translate(mTransform, glm::vec3(round(mPosition.x), round(mPosition.y), 0.0f));
	mTransform = glm::scale(mTransform, glm::vec3(mScale.x, mScale.y, 1.0f)); // change this to use scale
}

void Transform::HandleEvent(Event* pEvent) {
}

void Transform::SetScale(float scaleX, float scaleY) {
	mScale.x = scaleX;
	mScale.y = scaleY;
}

glm::mat4& Transform::getTransform() {
	return mTransform;
}

glm::vec3& Transform::GetScale() {
	return mScale;
}

void Transform::SetTrasform(glm::mat4 value) {
	mTransform = value;
}