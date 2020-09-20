/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector2D.h
Purpose: Header file for implementation of a simple Vector2D library
Language: C/C++, Microsoft Visual Studio 2019 C/C++ Compiler
Platform: Visual C++ 11 or above, Windows 7 & above
Project: CS529_dushyant.shukla_1
Author: Dushyant Shukla, dushyant.shukla, 60000519
Creation date: 09/18/2019
- End Header --------------------------------------------------------*/

#pragma once

class Vector2D {

	public:
	float x, y;

	public:

	Vector2D();
	Vector2D(const Vector2D& other);
	Vector2D(const float& value);
	Vector2D(const float& xCoordinate, const float& yCoordinate);
	~Vector2D();

	Vector2D& operator=(const Vector2D& other);
	Vector2D& operator=(const float& value);

	Vector2D operator*(const float& scalarConstact) const;
	Vector2D operator/(const float& scalarConstact) const;
	
	Vector2D& operator-=(const Vector2D& other);
	Vector2D operator-(const Vector2D& other) const;

	Vector2D& operator+=(const Vector2D& other);
	Vector2D operator+(const Vector2D& other) const;
	
	
	bool operator==(const Vector2D& other);

	float Dot(const Vector2D& other) const;
	Vector2D& Cross(const Vector2D& other) const;
	Vector2D& Negate();
	Vector2D& Normalize();
	float Length() const;
	float LengthSquare() const;
	float Distance(const Vector2D& other) const;
	float DistanceSquare(const Vector2D& other) const;
	
	friend Vector2D Normalize(const Vector2D& other);
	friend Vector2D Clamp(const Vector2D& value, const Vector2D& min, const Vector2D& max);
};