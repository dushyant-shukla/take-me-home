/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: LineSegment2D.c
Purpose: Implementation of a simple 2D line segment library. The file contains a single function defintion that builds the data of a 2D line segment.
Language: C/C++, Microsoft Visual Studio 2019 C/C++ Compiler
Platform: Visual C++ 11 or above, Windows 7 & above
Project: CS529_dushyant.shukla_2
Author: Dushyant Shukla
Student Username: dushyant.shukla
Student Id: 60000519
Creation date: 10/01/2019
- End Header --------------------------------------------------------*/

#include "LineSegment2D.h"
#include "Vector2D.h"


LineSegment2D* BuildLineSegment2D(Vector2D *Point0, Vector2D *Point1)
{
	LineSegment2D* lineSegment = new LineSegment2D();

	Vector2D edgeVector = Point1 - Point1;

	Vector2D normalVector;
	lineSegment->mN.x= edgeVector.y;
	lineSegment->mN.y = -edgeVector.x;
	lineSegment->mN.Normalize();

	lineSegment->mP0 = *Point0;
	lineSegment->mP1 = *Point1;
	lineSegment->mNdotP0 = Point0->Dot(lineSegment->mN);

	return lineSegment;
}