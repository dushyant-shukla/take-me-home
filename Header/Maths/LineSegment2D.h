/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: LineSegment2D.h
Purpose: Header file of a simple 2D line segment library. The file contains declaration of a single function that builds the data of a 2D line segment.
Language: C/C++, Microsoft Visual Studio 2019 C/C++ Compiler
Platform: Visual C++ 11 or above, Windows 7 & above
Project: CS529_dushyant.shukla_2
Author: Dushyant Shukla
Student Username: dushyant.shukla
Student Id: 60000519
Creation date: 10/01/2019
- End Header --------------------------------------------------------*/

#ifndef LINESEGMENT2D_H
#define LINESEGMENT2D_H

#include "Vector2D.h"



typedef struct LineSegment2D
{
	Vector2D mP0;		// Point on the line
	Vector2D mP1;		// Point on the line
	Vector2D mN;		// Line's normal
	float mNdotP0;		// To avoid computing it every time it's needed
}LineSegment2D;


/*
This function builds a 2D line segment's data using 2 points
 - Computes the normal (Unit Vector)
 - Computes the dot product of the normal with one of the points

 - Parameters
	- LS:		The to-be-built line segment
	- Point0:	One point on the line
	- Point1:	Another point on the line

 - Returns LineSegment2D if the line equation was built successfully 
*/
LineSegment2D* BuildLineSegment2D(Vector2D *Point0, Vector2D *Point1);




#endif