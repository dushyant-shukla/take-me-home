/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Math2D.c
Purpose: Implementation of a simple collision detection library
Language: C/C++, Microsoft Visual Studio 2019 C/C++ Compiler
Platform: Visual C++ 11 or above, Windows 7 & above
Project: CS529_dushyant.shukla_1
Author: Dushyant Shukla, dushyant.shukla, 60000519
Creation date: 09/17/2019
- End Header --------------------------------------------------------*/

#include "Math2D.h"
#include "stdio.h"
#include "math.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D* pP, Vector2D* pCenter, float Radius)
{

	double squareOfDistance = Vector2DSquareDistance(pP, pCenter);
	if (squareOfDistance < pow(Radius, 2)) {
		return 1;
	}
	return 0;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D* pPos, Vector2D* pRect, float Width, float Height)
{
	Vector2D rectangleBottomLeft = { pRect->x - 0.5f * Width, pRect->y - 0.5f * Height };
	Vector2D rectangleTopRight = { pRect->x + 0.5f * Width, pRect->y + 0.5f * Height };

	if ((pPos->x < rectangleBottomLeft.x) ||
		(pPos->x > rectangleTopRight.x) ||
		(pPos->y < rectangleBottomLeft.y) ||
		(pPos->y > rectangleTopRight.y)) {
		return 0;
	}
	return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D* pCenter0, float Radius0, Vector2D* pCenter1, float Radius1)
{
	double squareOfDistanceBetweenTheCenters = Vector2DSquareDistance(pCenter0, pCenter1);
	if (squareOfDistanceBetweenTheCenters <= pow((double)Radius0 + (double)Radius1, 2)) {
		return 1;
	}
	return 0;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D* pRect0, float Width0, float Height0, Vector2D* pRect1, float Width1, float Height1)
{
	// Rectangle#0
	Vector2D rectangle0BottomLeft = { pRect0->x - 0.5f * Width0, pRect0->y - 0.5f * Height0 };
	Vector2D rectangle0TopRight = { pRect0->x + 0.5f * Width0, pRect0->y + 0.5f * Height0 };

	// Rectangle#1 
	Vector2D rectangle1BottomLeft = { pRect1->x - 0.5f * Width1, pRect1->y - 0.5f * Height1 };
	Vector2D rectangle1TopRight = { pRect1->x + 0.5f * Width1, pRect1->y + 0.5f * Height1 };

	if ((rectangle0TopRight.x < rectangle1BottomLeft.x) ||
		(rectangle0BottomLeft.x > rectangle1TopRight.x) ||
		(rectangle0BottomLeft.y > rectangle1TopRight.y) ||
		(rectangle0TopRight.y < rectangle1BottomLeft.y)) {
		return 0;
	}
	return 1;
}



//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{
	return Vector2DDotProduct(P, &LS->mN) - (LS->mNdotP0);
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{
	return AnimatedCircleToStaticLineSegment(Ps, Pe, 0.0f, LS, Pi);
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{
	Vector2D frameVelocity;
	Vector2D intersectionPoint;
	float intersectionTime;
	float d;

	Vector2DSub(&frameVelocity, Pe, Ps);

	float distanceP0AndPs = StaticPointToStaticLineSegment(Ps, LS);
	float distanceP0AndPe = StaticPointToStaticLineSegment(Pe, LS);

	/* Conditions for non-collision */
	if (((distanceP0AndPs < - Radius) && (distanceP0AndPe < - Radius)) || ((distanceP0AndPs > Radius) && (distanceP0AndPe > Radius))) {
		return -1.0f;
	}

	if (distanceP0AndPs > 0) {
		d = Radius;
	}
	else {
		d = -Radius;
	}

	intersectionTime = (LS->mNdotP0 - Vector2DDotProduct(&LS->mN, Ps) + d) / Vector2DDotProduct(&LS->mN, &frameVelocity);

	if (0.0f <= intersectionTime && intersectionTime <= 1) {
	
		Vector2DScaleAdd(&intersectionPoint, &frameVelocity, Ps, intersectionTime);

		Vector2D P0PiEdgeVector;
		Vector2DSub(&P0PiEdgeVector, &intersectionPoint, &LS->mP0);

		Vector2D P1PiEdgeVector;
		Vector2DSub(&P1PiEdgeVector, &intersectionPoint, &LS->mP1);

		Vector2D P0P1EdgeVector;
		Vector2DSub(&P0P1EdgeVector, &LS->mP1, &LS->mP0);

		Vector2D P1P0EdgeVector;
		Vector2DNeg(&P1P0EdgeVector, &P0P1EdgeVector);

		/* Conditions for collision with infinite extention of the line segment */
		if ((Vector2DDotProduct(&P0PiEdgeVector, &P0P1EdgeVector) < 0) || (Vector2DDotProduct(&P1PiEdgeVector, &P1P0EdgeVector) < 0)) {
			return -1.0f;
		}

		*Pi = intersectionPoint;
	}

	return intersectionTime;
}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	return ReflectAnimatedCircleOnStaticLineSegment(Ps, Pe, 0.0f, LS, Pi, R);
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	float intersectionTime = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);

	if (0.0f <= intersectionTime && intersectionTime <= 1) {
		Vector2D PiPeEdgeVector;
		Vector2DSub(&PiPeEdgeVector, Pe, Pi);

		Vector2D PiPeReflectionEdgeVector;
		Vector2DScaleAdd(&PiPeReflectionEdgeVector, &LS->mN, &PiPeEdgeVector, (-2) * Vector2DDotProduct(&PiPeEdgeVector, &LS->mN));
		*R = PiPeReflectionEdgeVector;
		return intersectionTime;
	}

	return -1.0f;
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{
	return AnimatedCircleToStaticCircle(Ps, Pe, 0.0f, Center, Radius, Pi);
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	return ReflectAnimatedCircleOnStaticCircle(Ps, Pe, 0.0f, Center, Radius, Pi, R);
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{
	Vector2D frameVelocity;
	Vector2D Center0sToCenter1EdgeVector;
	float intersectionTime;
	float a, b, c, discriminant, sqrtDiscriminant;
	float time1, time2;

	Vector2DSub(&frameVelocity, Center0e, Center0s);

	Vector2DSub(&Center0sToCenter1EdgeVector, Center1, Center0s);
	//Vector2DSub(&Center0sToCenter1EdgeVector, Center0s, Center1);

	a = Vector2DDotProduct(&frameVelocity, &frameVelocity);
	b = -2 * Vector2DDotProduct(&Center0sToCenter1EdgeVector, &frameVelocity);
	c = Vector2DDotProduct(&Center0sToCenter1EdgeVector, &Center0sToCenter1EdgeVector) - ((Radius0 + Radius1) * (Radius0 + Radius1));

	discriminant = (b * b) - (4 * a * c);
	sqrtDiscriminant = sqrt(discriminant);

	if (discriminant > 0) { /* the animated intersects with the static circle */
		
		time1 = (-b - sqrtDiscriminant) / (2 * a);
		time2 = (-b + sqrtDiscriminant) / (2 * a);

		intersectionTime = time1 < time2 ? time1 : time2;

		if (0.0f <= intersectionTime && intersectionTime <= 1) {
			Vector2DScaleAdd(Pi, &frameVelocity, Center0s, intersectionTime);
		}

		return intersectionTime;
	}
	
	return -1.0f;
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{
	float intersectionTime = AnimatedCircleToStaticCircle(Center0s, Center0e, Radius0, Center1, Radius1, Pi);

	if (0.0f <= intersectionTime && intersectionTime <= 1) {

		Vector2D frameVelocity;
		Vector2D Center1ToPiEdgeVector;
		Vector2D PiToCenter0sEdgeVector;
		Vector2D NegPiToCenter0sEdgeVector;

		Vector2DSub(&frameVelocity, Center0e, Center0s);
		Vector2DSub(&Center1ToPiEdgeVector, Pi, Center1);
		Vector2DNormalize(&Center1ToPiEdgeVector, &Center1ToPiEdgeVector);
		Vector2DSub(&PiToCenter0sEdgeVector, Center0s, Pi);
		Vector2DNeg(&NegPiToCenter0sEdgeVector, &PiToCenter0sEdgeVector);

		Vector2DScaleAdd(R, &Center1ToPiEdgeVector, &NegPiToCenter0sEdgeVector, 2 * Vector2DDotProduct(&PiToCenter0sEdgeVector, &Center1ToPiEdgeVector));

		return intersectionTime;
	}

	return -1.0f;
}
