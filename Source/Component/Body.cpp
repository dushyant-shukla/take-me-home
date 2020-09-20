/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Body.cpp
Purpose: RigidBody component for game object through which physics can be applied
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

#include "RenderManager.h"

#include "Body.h"
#include "GameObject.h"
#include "Transform.h"
#include "Controller.h"
#include "CollisionManager.h"
#include "Map.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Body::Body() : Component(COMPONENT_TYPE::COMPONENT_BODY),
mAcceleration(0.0f), mInvMass(0.0f), mMass(0.0f),
mPosition(0.0f), mVelocity(0.0f), mPreviousPosition(0.0f),
mTotalForce(0.0f), mpShape(nullptr), mUseForce(false), mpController(nullptr), mpTransform(nullptr),
mPushedRightWall(false), mPushesRightWall(false), mPushedLeftWall(false), mPushesLeftWall(false),
mIsOnGround(false), mWasOnGround(false), mIsAtCeiling(false), mWasAtCeiling(false), mPreviousVeloctiy(0.0f), mFacingLeft(false), mFacingRight(true) {
}

Body::~Body() {
	delete mpShape;
}

void Body::Update() {
	Shape* pShape = this->GetShape();
	pShape->Update();
}

void Body::UpdateTotalForce(float dForceX, float dForceY) {
	mTotalForce.x = dForceX;
	mTotalForce.y = dForceY;
}

Shape* Body::GetShape() {
	return mpShape;
}

glm::vec3 Body::GetPosition() {
	return mPosition;
}

glm::vec3 Body::GetPreviousPosition() {
	return mPreviousPosition;
}

void Body::SetPosition(float x, float y) {
	mPosition.x = x;
	mPosition.y = y;
}

void Body::SetPosition(const glm::vec3& other) {
	mPosition = other;
}

void Body::SetPositionToPreviousPosition() {
	mPosition = mPreviousPosition;
}

glm::vec3 Body::GetVelocity() {
	return mVelocity;
}

void Body::SetVelocity(float x, float y) {
	mVelocity.x = x;
	mVelocity.y = y;
}

void Body::SetVelocity(const glm::vec3& other) {
	mVelocity = other;
}

void Body::UpdateVelocity(const glm::vec3& value) {
	mVelocity += value;
}

float Body::GetInverseMass() {
	return mInvMass;
}

void Body::MoveUp() {
	mVelocity.y = -mWalkSpeed;
}

void Body::MoveDown() {
	mVelocity.y = mWalkSpeed;
}

void Body::MoveRight() {
	if (mPushesRightWall) {
		mVelocity.x = 0.0f;
	}
	else {
		mVelocity.x = mWalkSpeed;
	}
	if (mCurrentState != GameObjectUtility::GameObjectUtility::CHARACTER_STATE::JUMP) {
		mCurrentState = GameObjectUtility::CHARACTER_STATE::WALK;
	}
	mFacingRight = true;
	mFacingLeft = false;
}

void Body::MoveLeft() {
	if (mPushesLeftWall) {
		mVelocity.x = 0.0f;
	}
	else {
		mVelocity.x = -mWalkSpeed;
	}
	if (mCurrentState != GameObjectUtility::CHARACTER_STATE::JUMP) {
		mCurrentState = GameObjectUtility::CHARACTER_STATE::WALK;
	}
	mFacingLeft = true;
	mFacingRight = false;
}

void Body::Jump() {
	if (mCurrentState != GameObjectUtility::CHARACTER_STATE::JUMP) { // this can later be replaced with a boolean variable that tells whether the character is on the ground or not
		mVelocity.y = -mJumpSpeed;
		//std::cout << "SETTING CURRENT STATE TO:: " << GameObjectUtility::CHARACTER_STATE::JUMP;
		mCurrentState = GameObjectUtility::CHARACTER_STATE::JUMP;
	}

	// also we can allow to jump again when jump is pressed longer but still limiting the max jump
}

void Body::Initialize() {
	mpTransform = static_cast<Transform*> (this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	if (nullptr != mpTransform) {
		mPreviousPosition = mPosition = mpTransform->GetPosition();
	}

	mpController = static_cast<Controller*> (this->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_CONTROLLER));
}

void Body::Serialize(Json::Value componentData) {
	mMass = componentData["mass"].asFloat();
	if (mMass != 0.0f) {
		mInvMass = 1.0f / mMass;
	}
	else {
		mInvMass = 0.0f;
	}

	if (componentData["use-force"] != Json::nullValue) {
		mUseForce = componentData["use-force"].asBool();
	}
	else {
		mUseForce = false;
	}

	if (componentData["walk-speed"] != Json::nullValue) {
		mWalkSpeed = componentData["walk-speed"].asFloat();
		mVelocity = glm::vec3(mWalkSpeed, 0.0f, 0.0f);
		mVelocity.x = mWalkSpeed;
	}

	if (componentData["jump-speed"] != Json::nullValue) {
		mJumpSpeed = componentData["jump-speed"].asFloat();
	}

	if (componentData["is-on-ground"] != Json::nullValue) {
		mIsOnGround = componentData["is-on-ground"].asFloat();
	}

	if (componentData["shape"]["type"] != Json::nullValue) {
		std::string shapeType = componentData["shape"]["type"].asString();
		if (shapeType._Equal("Circle")) {
			ShapeCircle* circle = new ShapeCircle();
			circle->SetOwnerBody(this);
			if (componentData["shape"]["radius"] != Json::nullValue) {
				circle->SetRadius(componentData["shape"]["radius"].asFloat());
			}
			this->mpShape = circle;
		}
		else if (shapeType._Equal("AABB")) {
			ShapeAABB* shapeAABB = new ShapeAABB();
			if (componentData["shape"]["size-x"] != Json::nullValue && componentData["shape"]["size-y"] != Json::nullValue) {
				shapeAABB->SetSize(glm::vec3(componentData["shape"]["size-x"].asFloat(), componentData["shape"]["size-y"].asFloat(), 0.0f));
			}
			shapeAABB->SetOwnerBody(this);
			this->mpShape = shapeAABB;
		}
	}
}

void Body::Integrate(float gravity, float deltaTime) {
	mPushedLeftWall = mPushesLeftWall;
	mPushedRightWall = mPushesRightWall;
	mWasOnGround = mIsOnGround;
	mWasAtCeiling = mIsAtCeiling;

	mPreviousPosition = mPosition;

	if (this->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL || this->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::MISSILE || this->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::BULLET) {
		mPosition += mVelocity * deltaTime;
		RenderManager::ClampToViewPort(mPosition, mpTransform->GetScale());
		if (mMass != 0.0 && mpTransform != nullptr) {
			mpTransform->GetPosition() = mPosition;
		}
		else {
			mPosition = mpTransform->GetPosition();
		}

		glm::mat4 mTransform = glm::mat4(1.0f);
		mTransform = glm::translate(mTransform, glm::vec3(round(mPosition.x), round(mPosition.y), 0.0f));
		mTransform = glm::scale(mTransform, glm::vec3(mpTransform->GetScale().x, mpTransform->GetScale().y, 1.0f)); // change this to use scale
		mpTransform->SetTrasform(mTransform);

		mpShape->SetCenter(glm::vec3(mPosition.x + (mpTransform->GetScale().x / 2), mPosition.y + (mpTransform->GetScale().y / 2), 0.0f));
		return;
	}
	else {
		if (mCurrentState == GameObjectUtility::CHARACTER_STATE::JUMP && !mIsOnGround) {
			mTotalForce.y += gravity;
			mAcceleration = mTotalForce * mInvMass;
			mVelocity += mAcceleration * deltaTime;
		}

		if (this->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER) {
			if (std::abs(mVelocity.y) > 400.0f) {
				if (mVelocity.y < 0.0f) {
					mVelocity.y = -400.0f;
				}
				else {
					mVelocity.y = 400.0f;
				}
			}

			if (std::abs(mVelocity.x) > 165.0f) {
				if (mVelocity.x < 0.0f) {
					mVelocity.x = -165.0f;
				}
				else {
					mVelocity.x = 165.0f;
				}
			}
		}

		mPosition += mVelocity * deltaTime;

		mTotalForce.x = 0.0f;
		mTotalForce.y = 0.0f;

		RenderManager::ClampToViewPort(mPosition, mpTransform->GetScale());

		if (mCurrentState == GameObjectUtility::CHARACTER_STATE::JUMP) {
			mIsOnGround = false;
		}
		else if (mCurrentState != GameObjectUtility::CHARACTER_STATE::JUMP) {
			mVelocity.x = 0.0f;
			mVelocity.y = 0.0f;
		}
	}

	if (mMass != 0.0 && mpTransform != nullptr) {
		mpTransform->GetPosition() = mPosition;
	}
	else {
		mPosition = mpTransform->GetPosition();
	}

	if (this->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER /*&& mCurrentState != GameObjectUtility::CHARACTER_STATE::STAND*/) {
		glm::vec3 scale = mpTransform->GetScale();
		float x = scale.x;
		float posX = mPosition.x;
		float rotationAngle = -270;
		//rotationAngle = -glm::mix(rotationAngle, 270.0f, 0.5f);
		if (mFacingLeft) {
			rotationAngle = -rotationAngle;
			x = -x;
			posX = posX + scale.x;
		}

		if (mCurrentState == GameObjectUtility::CHARACTER_STATE::STAND) {
			rotationAngle = 0.0f;
		}
		else if (mCurrentState == GameObjectUtility::CHARACTER_STATE::JUMP) {
			if (rotationAngle < 0) {
				rotationAngle += 0.5;
			}
			else {
				rotationAngle -= 0.5;
			}
		}

		glm::mat4 mTransform = glm::mat4(1.0f);
		//mTransform = glm::translate(mTransform, glm::vec3(round(mPosition.x), round(mPosition.y), 0.0f));
		mTransform = glm::translate(mTransform, glm::vec3(round(posX), round(mPosition.y), 0.0f));

		mTransform = glm::translate(mTransform, glm::vec3(0.5f * x, 0.5f * scale.y, 0.0f));
		mTransform = glm::rotate(mTransform, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		mTransform = glm::translate(mTransform, glm::vec3(-0.5f * x, -0.5f * scale.y, 0.0f));

		/*if (mVelocity.x < 0.0f) {
			scale.x = -scale.x;
		}*/
		mTransform = glm::scale(mTransform, glm::vec3(x, scale.y, 0.0f)); // change this to use scale
		mpTransform->SetTrasform(mTransform);
	}
	else {
		glm::mat4 mTransform = glm::mat4(1.0f);
		mTransform = glm::translate(mTransform, glm::vec3(round(mPosition.x), round(mPosition.y), 0.0f));
		mTransform = glm::scale(mTransform, glm::vec3(mpTransform->GetScale().x, mpTransform->GetScale().y, 1.0f)); // change this to use scale
		mpTransform->SetTrasform(mTransform);
	}

	mpShape->SetCenter(glm::vec3(mPosition.x + (mpTransform->GetScale().x / 2), mPosition.y + (mpTransform->GetScale().y / 2), 0.0f));
}

void Body::HandleEvent(Event* pEvent) {
}

void Body::SetIsOnGround(bool value) {
	mWasOnGround = mIsOnGround;
	mIsOnGround = value;
}

void Body::SetPushesRightWall(bool value) {
	mPushedRightWall = mPushesRightWall;
	mPushesRightWall = value;
}

void Body::SetPushesLeftWall(bool value) {
	mPushedLeftWall = mPushesLeftWall;
	mPushesLeftWall = value;
}

void Body::SetIsAtCeiling(bool value) {
	mWasAtCeiling = mIsAtCeiling;
	mIsAtCeiling = value;
}

bool Body::GetIsOnGround() {
	return mIsOnGround;
}

bool Body::GetPushesRightWall() {
	return mPushesRightWall;
}

bool Body::GetPushesLeftWall() {
	return mPushesLeftWall;
}

bool Body::GetIsAtCeiling() {
	return mIsAtCeiling;
}

Transform* Body::GetTransform() {
	return mpTransform;
}

Controller* Body::GetController() {
	return mpController;
}

GameObjectUtility::CHARACTER_STATE Body::GetCurrentState() {
	return mCurrentState;
}

void Body::SetStateToJumping() {
	mCurrentState = GameObjectUtility::CHARACTER_STATE::JUMP;
}

void Body::SetStateToWalking() {
	mCurrentState = GameObjectUtility::CHARACTER_STATE::WALK;
}

void Body::SetStateToStanding() {
	mCurrentState = GameObjectUtility::CHARACTER_STATE::STAND;
}

void Body::SetStateToDead() {
	mCurrentState = GameObjectUtility::CHARACTER_STATE::DEAD;
}

bool Body::IsJumping() {
	return mCurrentState == GameObjectUtility::CHARACTER_STATE::JUMP;
}

bool Body::IsWalking() {
	return mCurrentState == GameObjectUtility::CHARACTER_STATE::WALK;
}

bool Body::IsStanding() {
	return mCurrentState == GameObjectUtility::CHARACTER_STATE::STAND;
}

bool Body::IsFacingLeft() {
	return mFacingLeft;
}

bool Body::IsFacingRight() {
	return mFacingRight;
}

void Body::SetFacingLeft(bool value) {
	mFacingLeft = value;
}

void Body::SetFacingRight(bool value) {
	mFacingRight = value;
}