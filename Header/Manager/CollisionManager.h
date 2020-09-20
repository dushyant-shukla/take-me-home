/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollisionManager.h
Purpose: Skeleton for Collsion.cpp
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
#include "list"

#include <glm/glm.hpp>

#include "GameObjectUtility.h"

class Contact;
class Shape;
class Body;
class Map;

class Shape {

	public:
	enum class SHAPE_TYPE {
		CIRCLE,
		RECTANGLE,
		NUM
	};

	Shape(SHAPE_TYPE type);
	virtual ~Shape();

	virtual bool TestPoint(float pointX, float pointY) = 0;

	void SetOwnerBody(Body* body);
	void SetCenter(glm::vec3& value);
	glm::vec3& GetPreviousCenter();

	Body* GetOwnerBody();
	SHAPE_TYPE GetType();
	glm::vec3& GetCenter();

	virtual void Update() = 0;

	private:
	SHAPE_TYPE mType;
	Body* mpOwnerBody;
	glm::vec3 center;
	glm::vec3 previousCenter;
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


class ShapeCircle : public Shape {

	public:
	ShapeCircle();
	~ShapeCircle();

	bool TestPoint(float pointX, float pointY);
	
	float GetRadius();
	void SetRadius(float radius);

	void Update();

	private:
	float mRadius;
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


class ShapeAABB : public Shape {

	public:
	ShapeAABB();
	~ShapeAABB();

	bool TestPoint(float pointX, float pointY);
	
	void SetSize(glm::vec3 sizeValue);
	void SetHalfSize(glm::vec3 halfSizeValue);

	glm::vec3& GetSize();
	glm::vec3& GetHalfSize();

	void Update();

	private:

	glm::vec3 size;
	glm::vec3 halfSize;

};


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


class Contact {

	private:
	Body* mBodies[2];
	float mPenetration;
	glm::vec3 mNormal;

	public:
	void SetBody(int index, Body* pBody) {
		mBodies[index] = pBody;
	}

	Body* GetBody(int index) {
		return mBodies[index];
	}

	void SetPenetration(float penetration) {
		mPenetration = penetration;
	}

	void SetNormal(glm::vec3 normal) {
		mNormal = normal;
	}

	glm::vec3 GetNormal() {
		return mNormal;
	}
};


class CollisionData {

public:
	CollisionData() {
	}
	~CollisionData() {
	}

	Body* body1;
	Body* body2;
	glm::vec3 overlap;
	glm::vec3 velocity1;
	glm::vec3 velocity2;
	glm::vec3 previousPosition1;
	glm::vec3 previousPosition2;
	glm::vec3 position1;
	glm::vec3 position2;
};


/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

class CollisionManager {

	public:
	CollisionManager();
	~CollisionManager();

	void Reset();
	bool CheckCollisionAndGenerateContact(Body* body1, Body* body2);
	void ResolveCollision(CollisionData* contact);

	/*
		The function checks whether the object collides with a gound tile.
		It returns true if the object overlaps with any of the bottom tiles.
		Variable groundy holds the Y position of the top of the tile the object is colliding.
	*/
	bool HasGround(Map* map, Body* body, float& groundY);
	bool HasLeftWall(Map* map, Body* body, float& groundY);
	bool HasRightWall(Map* map, Body* body, float& groundY);
	bool HasCeilingWall(Map* map, Body* body, float& groundY);

	static glm::vec3 Lerp(const glm::vec3& A, const glm::vec3& B, float t);

	std::list<CollisionData*> mContacts;

	private:
	bool (*CollisionFunctions[(unsigned int)Shape::SHAPE_TYPE::NUM][(unsigned int)Shape::SHAPE_TYPE::NUM]) (Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]);
	bool collisionMatrix[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM];

};

bool CheckCollisionCircleCircle(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool (&collisionMatrix) [(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]);
bool CheckCollisionAabbAabb(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]);
bool CheckCollisionCircleAabb(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]);
bool CheckCollisionAabbCircle(Body* body1, Body* body2, std::list<CollisionData*>& contacts, bool(&collisionMatrix)[(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM][(unsigned int)GameObjectUtility::OBJECT_TYPE::NUM]);