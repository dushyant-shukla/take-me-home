/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsManager.cpp
Purpose: Resolves changes to the gameobject caused by physical forces
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

#include "PhysicsManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Body.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "LevelManager.h"
#include "Transform.h"
#include "Controller.h"

#include <iostream>

extern GameObjectManager* gameObjectManager;
extern CollisionManager* collisionManager;
extern EventManager* eventManager;
extern LevelManager* levelManager;

PhysicsManager::PhysicsManager() {
}

PhysicsManager::~PhysicsManager() {
}

void PhysicsManager::Update(float frameTime) {
	for (auto go : gameObjectManager->GetGameObjects()) {
		Body* pBody = static_cast<Body*> (go->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
		if (pBody != nullptr) {
			pBody->Integrate(800.0f, frameTime);
			//std::cout << "";
		}
	}

	// Moveable object to Tile Map collisions
	for (auto go : gameObjectManager->GetGameObjects()) {
		Body* pBody = static_cast<Body*> (go->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));
		//if (pBody->GetTransform()->GetPosition().y + pBody->GetTransform()->GetScale().y >= 512.0f) {
		//	//std::cout << "\nFound correct coordinate....\n";
		//}

		if (pBody != nullptr/* && pBody->GetController() != nullptr*/) {
			/*if (pBody->GetPosition().x == 3168.0f && pBody->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER) {
				//std::cout << "\nHAHAHA";
			}*/

			float leftWallX = -1.0f;
			float ceilingY = -1.0f;
			float rightWallX = -1.0f;
			float groundY = -1.0;

			bool mPushesLeftWall = false;

			glm::vec3 velocity = pBody->GetVelocity();
			glm::vec3 oldPosition = pBody->GetPreviousPosition();
			glm::vec3 position = pBody->GetPosition();

			Shape* shape = pBody->GetShape();
			glm::vec3 center = shape->GetCenter();
			Shape::SHAPE_TYPE shapeType = shape->GetType();
			if (Shape::SHAPE_TYPE::RECTANGLE == shapeType) {
				ShapeAABB* aabb = (ShapeAABB*)shape;
				glm::vec3 halfSize = aabb->GetHalfSize();

				// left wall
				if (velocity.x <= 0.0f
					&& collisionManager->HasLeftWall(levelManager->GetActiveMap(), pBody, leftWallX)) {
					if (oldPosition.x + (2 * halfSize.x) - leftWallX >= 2 * halfSize.x) {
						//if (oldPosition.x + (2 * halfSize.x) >= leftWallX) {
						position.x = leftWallX; // align the shape to the right wall of the tile.
						pBody->SetPosition(position);
						pBody->SetPushesLeftWall(true);
						if (pBody->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER) {
							velocity.x = std::max(velocity.x, 0.0f);
							pBody->SetVelocity(velocity);
						}
					}
				}
				else {
					pBody->SetPushesLeftWall(false);
				}

				// right wall
				if (velocity.x >= 0.0f
					&& collisionManager->HasRightWall(levelManager->GetActiveMap(), pBody, rightWallX)) {
					if (oldPosition.x + (2 * halfSize.x) <= rightWallX) {
						position.x = rightWallX - (2 * halfSize.x);
						pBody->SetPosition(position);
						pBody->SetPushesRightWall(true);
						if (pBody->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER) {
							velocity.x = std::min(velocity.x, 0.0f);
							pBody->SetVelocity(velocity);
						}
					}
				}
				else {
					pBody->SetPushesRightWall(false);
				}

				// ground
				if (velocity.y >= 0.0f
					&& collisionManager->HasGround(levelManager->GetActiveMap(), pBody, groundY)) {
					if (pBody->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER) {
						velocity.y = 0.0f;
						pBody->SetVelocity(velocity);
					}
					position.y = groundY - (2 * halfSize.y);
					pBody->SetPosition(position);
					pBody->SetIsOnGround(true);
					if (pBody->GetPreviousPosition().x != pBody->GetPosition().x) {
						pBody->SetStateToWalking();
					}
					else {
						pBody->SetStateToStanding();
					}
				}
				else {
					if (pBody->IsWalking() || pBody->IsStanding()) {
						pBody->SetStateToJumping();
						pBody->SetIsOnGround(false);
					}
				}

				// ceiling
				if (velocity.y <= 0.0f
					&& collisionManager->HasCeilingWall(levelManager->GetActiveMap(), pBody, ceilingY)) {
					////std::cout << "\nposition before: " << position.x << "\t" << position.y;
					if (pBody->GetPreviousPosition().y >= ceilingY) {
						position.y = ceilingY;
						////std::cout << "\nposition after: " << position.x << "\t" << position.y;
						velocity.y = 0.0f;
						pBody->SetVelocity(velocity);
						pBody->SetIsAtCeiling(true);
						pBody->SetPosition(position);
					}
				}
				else {
					pBody->SetIsAtCeiling(false);
				}
			}
			else {
				// for SHAPE CIRCLE to be implemented later
			}
		}
	}

	// Checking collision between objects
	collisionManager->Reset();

	if (gameObjectManager->GetGameObjects().empty() == false) {
		int index1 = 0;
		int index2 = 0;
		int size = gameObjectManager->GetGameObjects().size();

		for (; index1 < size; ++index1) {
			Body* pBody1 = static_cast<Body*> (gameObjectManager->operator[](index1)->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));

			if (nullptr == pBody1) {
				continue;
			}

			for (index2 = index1 + 1; index2 < size; ++index2) {
				Body* pBody2 = static_cast<Body*> (gameObjectManager->operator[](index2)->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));

				if (nullptr == pBody2) {
					continue;
				}

				glm::vec3 positionBody1 = pBody1->GetPosition();
				glm::vec3 positionBody2 = pBody2->GetPosition();
				//bool isCollision = collisionManager->CheckCollisionAndGenerateContact(pBody1->GetShape(), positionBody1.x, positionBody1.y, pBody2->GetShape(), positionBody2.x, positionBody2.y);
				bool isCollision = collisionManager->CheckCollisionAndGenerateContact(pBody1, pBody2);
				if (isCollision) {
					//std::cout << "\nCollision Detected!!" << std::endl;
				}
			}
		}
	}

	// Collision Resolution
	for (auto contacs : collisionManager->mContacts) {
		//CollisionEvent collisionEvent;

		//collisionEvent.mpObject1 = contacs->GetBody(0)->GetOwner();
		//collisionEvent.mpObject2 = contacs->GetBody(1)->GetOwner();

		collisionManager->ResolveCollision(contacs);

		//eventManager->BroadCastEventToSubscribers(&collisionEvent);
	}
}