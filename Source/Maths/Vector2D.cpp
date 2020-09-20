/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector2D.c
Purpose: Implementation of a simple Vector2D library
Language: C/C++, Microsoft Visual Studio 2019 C/C++ Compiler
Platform: Visual C++ 11 or above, Windows 7 & above
Project: CS529_dushyant.shukla_1
Author: Dushyant Shukla, dushyant.shukla, 60000519
Creation date: 09/18/2019
- End Header --------------------------------------------------------*/

#include "Vector2D.h"
#include <utility>

#define EPSILON 0.0001
#define PI 3.14159265

Vector2D::Vector2D() : x(0.0f), y(0.0f) {
}

Vector2D::Vector2D(const Vector2D& other) : x(other.x), y(other.y) {
}

Vector2D::Vector2D(const float& value) : x(value), y(value) {
}

Vector2D::Vector2D(const float& xCoordinate, const float& yCoordinate) : x(xCoordinate), y(yCoordinate) {
}

Vector2D::~Vector2D() {
}

Vector2D& Vector2D::operator=(const Vector2D& other) {
	Vector2D temp(other);
	std::swap(x, temp.x);
	std::swap(y, temp.y);
	return *this;
}

Vector2D& Vector2D::operator=(const float& value) {
	x = value;
	y = value;
	return *this;
}

Vector2D Vector2D::operator*(const float& scalarConstact) const {
	Vector2D temp(*this);
	temp.x *= scalarConstact;
	temp.y *= scalarConstact;
	return temp;
}

Vector2D Vector2D::operator/(const float& scalarConstact) const {
	Vector2D temp(*this);
	temp.x /= scalarConstact;
	temp.y /= scalarConstact;
	return temp;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
	x += other.x;
	y += other.y;
	return *this;
}

bool Vector2D::operator==(const Vector2D& other) {
	return (((double)x - (double)other.x) < EPSILON) && 
		(((double)y - (double)other.y) < EPSILON);
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
	Vector2D temp(*this);
	temp += other;
	return temp;
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
	Vector2D temp(*this);
	temp -= other;
	return temp;
}

float Vector2D::Dot(const Vector2D& other) const {
	return x * other.x + y * other.y;
}

Vector2D& Vector2D::Cross(const Vector2D& other) const {
	// TODO to be 
	Vector2D temp;
	return temp;
}

Vector2D& Vector2D::Negate() {
	x = -x;
	y = -y;
	return *this;
}

Vector2D& Vector2D::Normalize() {
	double magnitude = Length();
	x /= magnitude;
	y /= magnitude;
	return *this;
}

Vector2D Normalize(const Vector2D& other) {
	Vector2D normalizedVector(other);
	normalizedVector.Normalize();
	return normalizedVector;
}

float Vector2D::Length() const {
	return sqrtf(LengthSquare());
}

float Vector2D::LengthSquare() const {
	return x * x + y * y;
}

float Vector2D::Distance(const Vector2D& other) const {
	return sqrtf(DistanceSquare(other));
}

float Vector2D::DistanceSquare(const Vector2D& other) const {
	return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
}

Vector2D Clamp(const Vector2D& value, const Vector2D& minValue, const Vector2D& maxValue) {
	// max (min , min(max, value))

	Vector2D temp;
	float minX = value.x < maxValue.x ? value.x : maxValue.x;
	temp.x = minValue.x > minX ? minValue.x : minX;

	float minY = value.y < maxValue.y ? value.y : maxValue.y;
	temp.y = minValue.y > minY ? minValue.y : minY;

	return temp;
}
