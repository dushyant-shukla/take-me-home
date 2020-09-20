
/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Body.h
Purpose: Skeleton for Body.cpp
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
Creation date: November 01, 2019.
- End Header --------------------------------------------------------*/

#pragma once
#include "Component.h"
#include "CollisionManager.h"
#include "Math2D.h"
#include "GameObjectUtility.h"

#include <glm/glm.hpp>

class Shape;
class Transform;
class Controller;

class Body : public Component {

public:

	Body();
	~Body();

	void Update();
	void Serialize(Json::Value json);
	void Initialize(void);
	void Integrate(float gravity, float deltaTime);

	glm::vec3 GetPosition();
	glm::vec3 GetPreviousPosition();
	void SetPosition(float x, float y);
	void SetPosition(const glm::vec3& other);
	void Body::SetPositionToPreviousPosition();

	glm::vec3 GetVelocity();
	void SetVelocity(float x, float y);
	void SetVelocity(const glm::vec3& other);
	void UpdateVelocity(const glm::vec3& value);

	float GetInverseMass();

	Shape* GetShape();

	void UpdateTotalForce(float dForceX, float dForceY);

	void HandleEvent(Event* pEvent);

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Jump();

	void SetIsOnGround(bool value);
	void SetPushesRightWall(bool value);
	void SetPushesLeftWall(bool value);
	void SetIsAtCeiling(bool value);

	bool GetIsOnGround();
	bool GetPushesRightWall();
	bool GetPushesLeftWall();
	bool GetIsAtCeiling();

	Transform* GetTransform();
	Controller* GetController();

	GameObjectUtility::CHARACTER_STATE GetCurrentState();
	bool IsJumping();
	bool IsWalking();
	bool IsStanding();
	bool IsFacingLeft();
	bool IsFacingRight();
	void SetStateToJumping();
	void SetStateToWalking();
	void SetStateToStanding();
	void SetStateToDead();
	void SetFacingLeft(bool value);
	void SetFacingRight(bool value);

private:
	glm::vec3 mPosition;
	glm::vec3 mPreviousPosition;

	glm::vec3 mVelocity;
	glm::vec3 mPreviousVeloctiy;

	//glm::vec3 mJumpVelocity;

	glm::vec3 mAcceleration;

	glm::vec3 mTotalForce;

	float mWalkSpeed;

	float mJumpSpeed;

	float mMass;
	float mInvMass;

	bool mUseForce;

	Controller* mpController;
	Transform* mpTransform;

	bool mPushedRightWall;
	bool mPushesRightWall;

	bool mPushedLeftWall;
	bool mPushesLeftWall;

	bool mWasOnGround;
	bool mIsOnGround;

	bool mWasAtCeiling;
	bool mIsAtCeiling;

	bool mFacingLeft;
	bool mFacingRight;

	Shape* mpShape;

	GameObjectUtility::CHARACTER_STATE mCurrentState;
};