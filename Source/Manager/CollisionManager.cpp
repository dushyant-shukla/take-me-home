/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollisionManager.cpp
Purpose: Checks and manages Collisions
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

//#include <GLFW/glfw3.h>
#include "CollisionManager.h"

#include "Body.h"
#include "Map.h"
#include "Controller.h"
#include "GameObject.h"
#include "Jumping.h"

#include "GameStateManager.h"

#include "RenderManager.h"

#include <iostream>
#include <cstdlib>
#include <glm/gtc/quaternion.hpp>

extern GLFWwindow* window;

////////////////////////////////////////////  SHAPE CLASS  ///////////////////////////////////////////////////////////////

Shape::Shape(SHAPE_TYPE type) : mType(type), mpOwnerBody(nullptr) {
}

Shape::~Shape() {
	// delete mpOwnerBody;
	// not calling delete mpOwnerBody as the body component associated with
	// the shape is ultimately deleted in ~GameObject()
}

void Shape::SetOwnerBody(Body* body) {
	mpOwnerBody = body;
}

Body* Shape::GetOwnerBody() {
	return mpOwnerBody;
}

Shape::SHAPE_TYPE Shape::GetType() {
	return mType;
}

glm::vec3& Shape::GetCenter() {
	return center;
}

void Shape::SetCenter(glm::vec3& value) {
	previousCenter = center;
	center = value;
}

glm::vec3& Shape::GetPreviousCenter() {
	return previousCenter;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////  SHAPE CIRCLE CLASS  ///////////////////////////////////////////////////////////

ShapeCircle::ShapeCircle() :Shape(SHAPE_TYPE::CIRCLE), mRadius(0.0f) {
}

ShapeCircle::~ShapeCircle() {
}

bool ShapeCircle::TestPoint(float pointX, float pointY) {
	glm::vec3 position = GetOwnerBody()->GetPosition();
	float sqDist = (pointX - position.x) * (pointX - position.x) + (pointY - position.y) * (pointY - position.y);

	if (sqDist > mRadius* mRadius) {
		return false;
	}

	return true;
}

float ShapeCircle::GetRadius() {
	return mRadius;
}

void ShapeCircle::SetRadius(float radius) {
	mRadius = radius;
}

void ShapeCircle::Update() {

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////// SHAPE RECTANGLE CLASS  //////////////////////////////////////////////////////

ShapeAABB::ShapeAABB() :Shape(SHAPE_TYPE::RECTANGLE), size(0.0f), halfSize(0.0f) {
}

ShapeAABB::~ShapeAABB() {
}

bool ShapeAABB::TestPoint(float pointX, float pointY) {
	return false;
}

void ShapeAABB::SetSize(glm::vec3 sizeValue) {
	size = sizeValue;
	SetHalfSize(glm::vec3(size.x / 2, size.y / 2, 0.0f));
}

void ShapeAABB::SetHalfSize(glm::vec3 halfSizeValue) {
	halfSize = halfSizeValue;
}

glm::vec3& ShapeAABB::GetSize() {
	return size;
}

glm::vec3& ShapeAABB::GetHalfSize() {
	return halfSize;
}

void ShapeAABB::Update() {

	glm::vec3 position = GetOwnerBody()->GetPosition();

	/*glm::vec3 bottomLeft = { position.x - 0.5f * mWidth, position.y - 0.5f * mHeight, 0.0f };
	glm::vec3 bottomRight = { position.x + 0.5f * mWidth, position.y - 0.5f * mHeight, 0.0f };
	glm::vec3 topRight = { position.x + 0.5f * mWidth, position.y + 0.5f * mHeight, 0.0f };
	glm::vec3 topLeft = { position.x - 0.5f * mWidth, position.y + 0.5f * mHeight, 0.0f };*/

	//boxSides[0] = BuildLineSegment2D(&bottomLeft, &topLeft); // left
	//boxSides[1] = BuildLineSegment2D(&topLeft, &topRight); // top
	//boxSides[2] = BuildLineSegment2D(&bottomRight, &topRight); // right
	//boxSides[3] = BuildLineSegment2D(&bottomLeft, &bottomRight); // bottom
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////  COLLISION MANAGER  /////////////////////////////////////////////////////////////////

CollisionManager::CollisionManager() {
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::CIRCLE][(unsigned int)Shape::SHAPE_TYPE::CIRCLE] = CheckCollisionCircleCircle;
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::RECTANGLE][(unsigned int)Shape::SHAPE_TYPE::RECTANGLE] = CheckCollisionAabbAabb;
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::CIRCLE][(unsigned int)Shape::SHAPE_TYPE::RECTANGLE] = CheckCollisionCircleAabb;
	CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::RECTANGLE][(unsigned int)Shape::SHAPE_TYPE::CIRCLE] = CheckCollisionAabbCircle;


	// collision combinations

	for (int i = 0; i < (unsigned int)GameObjectUtility::OBJECT_TYPE::NUM; ++i) {
		for (int j = 0; j < (unsigned int)GameObjectUtility::OBJECT_TYPE::NUM; ++j) {
			collisionMatrix[i][j] = false;
		}
	}

	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER][(unsigned int)GameObjectUtility::OBJECT_TYPE::MISSILE] = true;
	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::MISSILE][(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER] = true;

	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER][(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL] = true;
	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL][(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER] = true;

	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER][(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP] = true;
	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP][(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER] = true;

	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER][(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_TURRET] = true;
	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_TURRET][(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER] = true;

	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::BULLET][(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL] = true;
	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL][(unsigned int)GameObjectUtility::OBJECT_TYPE::BULLET] = true;

	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::BULLET][(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP] = true;
	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP][(unsigned int)GameObjectUtility::OBJECT_TYPE::BULLET] = true;

	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER][(unsigned int)GameObjectUtility::OBJECT_TYPE::HOME] = true;
	collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::HOME][(unsigned int)GameObjectUtility::OBJECT_TYPE::PLAYER] = true;
}

CollisionManager::~CollisionManager() {
	Reset();
}

void CollisionManager::Reset() {
	for (auto contact : mContacts) {
		delete contact;
	}
	mContacts.clear();
}

void CollisionManager::ResolveCollision(CollisionData* contact) {

	// Calculate relative velocity
	Body* bodyA = contact->body1;
	Body* bodyB = contact->body2;

	glm::vec3 normal = glm::normalize(contact->overlap);

	glm::vec3 velocityA = bodyA->GetVelocity();
	glm::vec3 velocityB = bodyB->GetVelocity();
	glm::vec3 relativeVelocity(velocityB.x - velocityA.x, velocityB.y - velocityA.y, 0.0f);

	// Calculate relative velocity in terms of the normal direction
	float velocityAlongNormal = glm::dot(relativeVelocity, normal);

	// Do not resolve if velocities are separating
	//if (velocityAlongNormal < 0) {
		// Calculate restitution
		float e = 1.0;

		// Calculate impulse scalar
		float j = (-(1 + e) * velocityAlongNormal) / (bodyA->GetInverseMass() + bodyB->GetInverseMass());

		// Apply impulse
		glm::vec3 impulse = normal * j;

		// Body1 is either PLAYER or BULLET at all times
		if (bodyA->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER) {
			switch (bodyB->GetOwner()->GetType()) {
			case GameObjectUtility::OBJECT_TYPE::MISSILE:
				
				if (contact->overlap.x > 0) { // Player is on the right side of the enemy
					velocityA.x += (165.0f * bodyA->GetInverseMass());
				}
				else {
					velocityA.x -= (165.0f * bodyA->GetInverseMass());
				}
				velocityA.y -= (400.0f * bodyA->GetInverseMass());
				if (std::abs(velocityA.y) > 400.0f) {
					if (velocityA.y < 0.0f) {
						velocityA.y = -400.0f;
					}
					else {
						velocityA.y = 400.0f;
					}
				}

				bodyA->SetVelocity(velocityA);
				bodyB->GetOwner()->SetIsActive(false);
				break;

			case GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL:
				if (contact->overlap.x > 0) { // Player is on the right side of the enemy
					velocityA.x += (impulse.x * 30.0f * bodyA->GetInverseMass());
					glm::vec3 position = bodyA->GetPosition();
					position.x = position.x + 10.0f;
					position.y = position.y - 20.0f;
					bodyA->SetPosition(position);
				}
				else {
					velocityA.x -= (impulse.x * 30.0f * bodyA->GetInverseMass());
					glm::vec3 position = bodyA->GetPosition();
					position.x = position.x - 10.0f;
					position.y = position.y - 20.0f;
					bodyA->SetPosition(position);
				}
				velocityA.y -= (impulse.y * 2.0f * bodyA->GetInverseMass());
				if (std::abs(velocityA.y) > 400.0f) {
					if (velocityA.y < 0.0f) {
						velocityA.y = -400.0f;
					}
					else {
						velocityA.y = 400.0f;
					}
				}

				bodyA->SetVelocity(velocityA);
				bodyB->SetVelocity(-bodyB->GetVelocity());
				break;

			case GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP:
				if (contact->overlap.x > 0) { // Player is on the right side of the enemy
					velocityA.x += (10.0f * bodyA->GetInverseMass());
				}
				else {
					velocityA.x -= (10.0f * bodyA->GetInverseMass());
				}
				velocityA.y -= (impulse.y * bodyA->GetInverseMass());
				bodyA->SetVelocity(velocityA);
				break;

			case GameObjectUtility::OBJECT_TYPE::ENEMY_TURRET:
				// no collision between the turret and the player
				break;

			case GameObjectUtility::OBJECT_TYPE::HOME:

				RenderManager::screenIndex = 1;
				SetNextGameState(GAME_STATE::GAME_INIT);
				//glfwSetWindowTitle(window, u8"YOU WIN!! PRESS ESCAPE TO RESTART");
				//SetRender(false);
				break;
			}
		
		}
		else {
			// Bullet behaviour

			switch (bodyB->GetOwner()->GetType()) {
			
			case GameObjectUtility::OBJECT_TYPE::ENEMY_PATROL:
				if (bodyA->GetVelocity().x < 0.0f) {
					if (std::abs(velocityB.x) >= 10.0f && velocityB.x > 0) {
						velocityB.x = velocityB.x - 60.0f;
					}
					else {
						velocityB.x = velocityB.x + 60.0f;
					}
				}
				else {
					velocityB.x = velocityB.x + 60.0f;
					if (std::abs(velocityB.x) >= 10.0f && velocityB.x > 0) {
						velocityB.x = velocityB.x - 60.0f;
					}
					else {
						velocityB.x = velocityB.x + 60.0f;
					}
				}
				bodyB->SetVelocity(velocityB);
				break;

			case GameObjectUtility::OBJECT_TYPE::ENEMY_JUMP:
				Jumping* jumpComponent = static_cast<Jumping*> (bodyB->GetOwner()->GetComponent(COMPONENT_TYPE::COMPONENT_JUMPING));
				jumpComponent->UpdateJumpSpeed(80.0f);
				break;

			}

			bodyA->GetOwner()->SetIsActive(false); // destroy the bullet
		}
		
		/*velocityA -= (impulse * bodyA->GetInverseMass());
		velocityB += (impulse * bodyB->GetInverseMass());
		bodyA->SetVelocity(velocityA);
		bodyB->SetVelocity(velocityB);*/

		//const float percent = 0.2f;
		//const float slop = 0.01f;
		//glm::vec3 correction = (std::max(contact->overlap.x > contact->overlap.y ? contact->overlap.x : contact->overlap.y - slop, 0.0f)) / (bodyA->GetInverseMass() + bodyB->GetInverseMass()) * percent * normal;
		//bodyA->SetPosition(bodyA->GetPosition() - bodyA->GetInverseMass() * correction);
		//bodyB->SetPosition(bodyB->GetPosition() - bodyB->GetInverseMass() * correction);
	//}

}


bool CollisionManager::CheckCollisionAndGenerateContact(Body* body1, Body* body2) {
	return CollisionFunctions[(unsigned int)body1->GetShape()->GetType()][(unsigned int)body2->GetShape()->GetType()](body1, body2, this->mContacts, this->collisionMatrix);
}

bool CheckCollisionCircleCircle(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]) {
	return false;
}

bool CheckCollisionAabbAabb(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]) {

	GameObjectUtility::OBJECT_TYPE type1 = body1->GetOwner()->GetType();
	GameObjectUtility::OBJECT_TYPE type2 = body2->GetOwner()->GetType();

	if (!collisionMatrix[(unsigned int)type1][(unsigned int)type2]) {
		return false; // if collision is not to be calculated between the pair of objects
	}

	ShapeAABB* pAABB1 = (ShapeAABB*)body1->GetShape();
	ShapeAABB* pAABB2 = (ShapeAABB*)body2->GetShape();

	glm::vec3 halfSize1 = pAABB1->GetHalfSize();
	glm::vec3 halfSize2 = pAABB2->GetHalfSize();

	glm::vec3 center1 = pAABB1->GetCenter();
	glm::vec3 center2 = pAABB2->GetCenter();

	glm::vec3 center1ToCenter2 = center2 - center1;
	glm::vec3 sumOfTheHalfSizes = halfSize1 + halfSize2;

	if (halfSize1.x == 0.0f || halfSize1.y == 00.f || halfSize2.x == 0.0f || halfSize2.y == 00.f) {
		return false;
	}

	if (abs(center1ToCenter2.x) > sumOfTheHalfSizes.x) {
		return false;
	}

	if (abs(center1ToCenter2.y) > sumOfTheHalfSizes.y) {
		return false;
	}

	int signOfXOverlap, signOfYOverlap;

	CollisionData* collisionData = new CollisionData();
	if (body1->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER || body1->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::BULLET) { // setting body 1 to be always either PLAYER OR BULLET
		if (center1.x - center2.x >= 0) {
			signOfXOverlap = 1;
		}
		else {
			signOfXOverlap = -1;
		}

		if (center1.y - center2.y >= 0) {
			signOfYOverlap = 1;
		}
		else {
			signOfYOverlap = -1;
		}
		collisionData->body1 = body1;
		collisionData->body2 = body2;
		collisionData->overlap = glm::vec3(signOfXOverlap * (sumOfTheHalfSizes.x - std::abs(center1.x - center2.x)), signOfYOverlap * (sumOfTheHalfSizes.y - std::abs(center1.y - center2.y)), 0.0f);
		collisionData->velocity1 = body1->GetVelocity();
		collisionData->velocity2 = body2->GetVelocity();
		collisionData->previousPosition1 = body1->GetPreviousPosition();
		collisionData->previousPosition2 = body2->GetPreviousPosition();
		collisionData->position1 = body1->GetPosition();
		collisionData->position2 = body2->GetPosition();
	}
	else {
		if (center2.x - center1.x >= 0) {
			signOfXOverlap = 1;
		}
		else {
			signOfXOverlap = -1;
		}

		if (center2.y - center1.y >= 0) {
			signOfYOverlap = 1;
		}
		else {
			signOfYOverlap = -1;
		}
		collisionData->body1 = body2;
		collisionData->body2 = body1;
		collisionData->overlap = glm::vec3(signOfXOverlap * (sumOfTheHalfSizes.x - std::abs(center2.x - center1.x)), signOfYOverlap * (sumOfTheHalfSizes.y - std::abs(center2.y - center1.y)), 0.0f);
		collisionData->velocity1 = body2->GetVelocity();
		collisionData->velocity2 = body1->GetVelocity();
		collisionData->previousPosition1 = body2->GetPreviousPosition();
		//collisionData->previousPosition2 = body1->GetPreviousPosition();
		collisionData->position1 = body2->GetPosition();
		collisionData->position2 = body1->GetPosition();
	}
	
	contacts.push_back(collisionData);

	return true;
}

bool CheckCollisionCircleAabb(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]) {
	return false;
}

bool CheckCollisionAabbCircle(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]) {
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														//////////////////////////////////////
////////////////////////////////////////////////////////// TILE MAP AND OBJECT COLLISIONS /////////////////////////////////////////////////////////////////////////
													  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CollisionManager::HasGround(Map* map, Body* body, float& groundY) {
	Shape* shape = body->GetShape();
	glm::vec3 newCenter = shape->GetCenter();
	glm::vec3 previousCenter = shape->GetPreviousCenter();
	Shape::SHAPE_TYPE shapeType = shape->GetType();

	groundY = 0.0f;

	if (Shape::SHAPE_TYPE::RECTANGLE == shapeType) {
		ShapeAABB* aabb = (ShapeAABB*)shape;
		glm::vec3 halfSize = aabb->GetHalfSize();

		glm::vec3 oldBottomLeft = glm::vec3(0.0f);
		glm::vec3 oldBottomRight = glm::vec3(0.0f);

		glm::vec3 newBottomLeft = glm::vec3(0.0f);
		glm::vec3 newBottomRight = glm::vec3(0.0f);

		oldBottomLeft.x = round(previousCenter.x - halfSize.x + 1.0f);
		oldBottomLeft.y = round(previousCenter.y + halfSize.y + 1.0f);

		newBottomLeft.x = round(newCenter.x - halfSize.x + 1.0f);
		newBottomLeft.y = round(newCenter.y + halfSize.y + 1.0f);

		newBottomRight.x = round(newCenter.x + halfSize.x - 1.0f);
		newBottomRight.y = round(newCenter.y + halfSize.y + 1.0f);

		int endY = map->GetMapTileYCoordinateByWorldPosition(newBottomLeft);
		int begY = std::max(map->GetMapTileYCoordinateByWorldPosition(oldBottomLeft) - 1, endY);
		int distance = std::max(std::abs(endY - begY), 1);
		//glm::vec3 bottomLeft = center - halfSize + glm::vec3(1.0f, 1.0f, 0.0f); // The sensor line is just one pixel below the AABB's bottom line
		//glm::vec3 bottomRight = center + halfSize + glm::vec3(-1.0f, 1.0f, 0.0f);

		int tileIndexX;

		for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY) {
			
			glm::vec3 bottomLeft = glm::vec3(1.0f);
			glm::vec3 bottomRight = glm::vec3(1.0f);

			bottomLeft = Lerp(newBottomLeft, oldBottomLeft, (float) std::abs(endY - tileIndexY) / distance);
			//bottomRight.x = bottomRight.x + halfSize.x * 2.0f - 2.0f;
			bottomRight.x = bottomLeft.x + halfSize.x * 2.0f - 2.0f;
			bottomRight.y = bottomLeft.y;

			for (glm::vec3 checkedTile = bottomLeft; ; checkedTile.x += TILE_SIZE) {
				//checkedTile.x = std::min(checkedTile.x, newBottomRight.x);
				checkedTile.x = std::min(checkedTile.x, bottomRight.x);
				tileIndexX = map->GetMapTileXCoordinateByWorldPosition(checkedTile);
				groundY = (float)tileIndexY * TILE_SIZE + map->GetPosition().y;
				if (map->IsTileObstacle(tileIndexX, tileIndexY, body->GetOwner()->GetType())) {
					return true;
				}
				if (checkedTile.x >= bottomRight.x) {
					break;
				}
			}
		}
		return false;
	}
	else {
		// for SHAPE CIRCLE to be implemented later
		return false;
	}
}

bool CollisionManager::HasLeftWall(Map* map, Body* body, float& positionX) {
	Shape* shape = body->GetShape();
	glm::vec3 newCenter = shape->GetCenter();
	glm::vec3 previousCenter = shape->GetPreviousCenter();
	Shape::SHAPE_TYPE shapeType = shape->GetType();

	positionX = 0.0f;

	if (Shape::SHAPE_TYPE::RECTANGLE == shapeType) {
		ShapeAABB* aabb = (ShapeAABB*)shape;
		glm::vec3 halfSize = aabb->GetHalfSize();

		glm::vec3 newBottomLeft = newCenter;
		glm::vec3 newTopLeft = newCenter;
		glm::vec3 oldBottomLeft = previousCenter;

		oldBottomLeft.x = round(oldBottomLeft.x - halfSize.x - 1.0f);
		oldBottomLeft.y = round(oldBottomLeft.y + halfSize.y - 1.0f);

		newBottomLeft.x = round(newBottomLeft.x - halfSize.x - 1.0f);
		newBottomLeft.y = round(newBottomLeft.y + halfSize.y - 1.0f);

		newTopLeft.x = round(newTopLeft.x - halfSize.x - 1.0f);
		newTopLeft.y = round(newTopLeft.y - halfSize.y + 1.0f);

		int tileIndexY;

		int endX = map->GetMapTileXCoordinateByWorldPosition(newBottomLeft);
		int begX = std::max(map->GetMapTileXCoordinateByWorldPosition(oldBottomLeft) - 1, endX);
		int distance = std::max(std::abs(endX - begX), 1);

		for (int tileIndexX = begX; tileIndexX >= endX; --tileIndexX)
		{
			glm::vec3 topLeft = glm::vec3(0.0f);
			glm::vec3 bottomLeft = glm::vec3(0.0f);
			
			bottomLeft = Lerp(newBottomLeft, oldBottomLeft, (float)std::abs(endX - tileIndexX) / distance);
			topLeft.y = bottomLeft.y - halfSize.y * 2.0f;
			topLeft.x = bottomLeft.x;

			for (glm::vec3 checkedTile = bottomLeft; ; checkedTile.y -= TILE_SIZE) {
				checkedTile.y = std::max(checkedTile.y, topLeft.y);
				tileIndexY = map->GetMapTileYCoordinateByWorldPosition(checkedTile);
				positionX = (float)(tileIndexX + 1) * TILE_SIZE + map->GetPosition().x;
				if (map->IsTileObstacle(tileIndexX, tileIndexY, body->GetOwner()->GetType())) {
					return true;
				}
				if (checkedTile.y <= topLeft.y) {
					break;
				}
				
			}
		}

		return false;
	}
	else {
		// for SHAPE CIRCLE to be implemented later
		return false;
	}
}

bool CollisionManager::HasRightWall(Map* map, Body* body, float& positionX) {
	Shape* shape = body->GetShape();
	glm::vec3 center = shape->GetCenter();
	Shape::SHAPE_TYPE shapeType = shape->GetType();
	if (Shape::SHAPE_TYPE::RECTANGLE == shapeType) {
		ShapeAABB* aabb = (ShapeAABB*)shape;
		glm::vec3 halfSize = aabb->GetHalfSize();
		glm::vec3 bottomRight = center;
		glm::vec3 topRight = center;

		bottomRight.x = round(bottomRight.x + halfSize.x + 1.0f);
		bottomRight.y = round(bottomRight.y + halfSize.y - 1.0f);

		topRight.x = round(topRight.x + halfSize.x + 1.0f);
		topRight.y = round(topRight.y - halfSize.y + 1.0f);

		glm::vec3 tileCoordinates;
		for (glm::vec3 checkedTile = bottomRight; ; checkedTile.y -= TILE_SIZE) {
			checkedTile.y = std::max(checkedTile.y, topRight.y);
			tileCoordinates = map->GetMapTileCoordinatesByWorldPosition(checkedTile);

			positionX = (float)tileCoordinates.x * TILE_SIZE - map->GetPosition().y;

			if (map->IsTileObstacle(tileCoordinates.x, tileCoordinates.y, body->GetOwner()->GetType())) {
				return true;
			}

			if (checkedTile.y <= topRight.y) {
				break;
			}
		}
		return false;
	}
	else {
		// for SHAPE CIRCLE to be implemented later
		return false;
	}
}

bool CollisionManager::HasCeilingWall(Map* map, Body* body, float& ceilingY) {
	Shape* shape = body->GetShape();
	glm::vec3 center = shape->GetCenter();
	Shape::SHAPE_TYPE shapeType = shape->GetType();
	if (Shape::SHAPE_TYPE::RECTANGLE == shapeType) {
		ShapeAABB* aabb = (ShapeAABB*)shape;
		glm::vec3 halfSize = aabb->GetHalfSize();
		glm::vec3 topLeft = center;
		glm::vec3 topRight = center;

		topLeft.x = round(topLeft.x - halfSize.x + 1.0f);
		topLeft.y = round(topLeft.y - halfSize.y - 1.0f);

		topRight.x = round(topRight.x + halfSize.x - 1.0f);
		topRight.y = round(topRight.y - halfSize.y - 1.0f);

		glm::vec3 tileCoordinates;
		for (glm::vec3 checkedTile = topLeft; checkedTile.x <= topRight.x; checkedTile.x += TILE_SIZE) {

			checkedTile.x = std::min(checkedTile.x, topRight.x);
			tileCoordinates = map->GetMapTileCoordinatesByWorldPosition(checkedTile);

			ceilingY = ((float)(tileCoordinates.y + 1)) * TILE_SIZE + map->GetPosition().y + 2.0f;
			if (map->IsTileObstacle(tileCoordinates.x, tileCoordinates.y, body->GetOwner()->GetType())) {
				return true;
			}
		}
		return false;
	}
	else {
		// for SHAPE CIRCLE to be implemented later
		return false;
	}
}

glm::vec3 CollisionManager::Lerp(const glm::vec3& vectorA, const glm::vec3& vectorB, float t) {
	return vectorA * t + vectorB * (1.0f - t);
}