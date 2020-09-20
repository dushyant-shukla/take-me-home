/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix2D.c
Purpose: Implementation of a simple Matrix2D library
Language: C/C++, Microsoft Visual Studio 2019 C/C++ Compiler
Platform: Visual C++ 11 or above, Windows 7 & above
Project: CS529_dushyant.shukla_1
Author: Dushyant Shukla, dushyant.shukla, 60000519
Creation date: 09/18/2019
- End Header --------------------------------------------------------*/

#include "Matrix2D.h"
#include <stdio.h>

#define PI 3.14159265

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D* pResult)
{
	Matrix2D identityMatrix = { {{1.0f,0,0}, {0,1.0f,0}, {0,0,1.0f}} };
	*pResult = identityMatrix;
}

// ---------------------------------------------------------------------------

void Matrix2DTransposeHelper(Matrix2D* pResult, Matrix2D* pMtx) {
	Matrix2D transposeMatrix = *pMtx;
	transposeMatrix.m[0][1] = pMtx->m[1][0];
	transposeMatrix.m[0][2] = pMtx->m[2][0];
	transposeMatrix.m[1][0] = pMtx->m[0][1];
	transposeMatrix.m[1][2] = pMtx->m[2][1];
	transposeMatrix.m[2][0] = pMtx->m[0][2];
	transposeMatrix.m[2][1] = pMtx->m[1][2];
	*pResult = transposeMatrix;
}

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D* pResult, Matrix2D* pMtx)
{
	if (pResult == pMtx) {
		Matrix2D temp;
		Matrix2DTransposeHelper(&temp, pMtx);
		*pResult = temp;
	}
	else {
		Matrix2DTransposeHelper(pResult, pMtx);
	}
}

// ---------------------------------------------------------------------------

void Matrix2DConcatenationHelper(Matrix2D* pResult, Matrix2D* pMtx0, Matrix2D* pMtx1) {
	Matrix2D concatMatrix;
	Matrix2DIdentity(&concatMatrix); // Initializing the matrix as identity 3x3 matrix

	concatMatrix.m[0][0] = pMtx0->m[0][0] * pMtx1->m[0][0] + pMtx0->m[0][1] * pMtx1->m[1][0] + pMtx0->m[0][2] * pMtx1->m[2][0];
	concatMatrix.m[0][1] = pMtx0->m[0][0] * pMtx1->m[0][1] + pMtx0->m[0][1] * pMtx1->m[1][1] + pMtx0->m[0][2] * pMtx1->m[2][1];
	concatMatrix.m[0][2] = pMtx0->m[0][0] * pMtx1->m[0][2] + pMtx0->m[0][1] * pMtx1->m[1][2] + pMtx0->m[0][2] * pMtx1->m[2][2];

	concatMatrix.m[1][0] = pMtx0->m[1][0] * pMtx1->m[0][0] + pMtx0->m[1][1] * pMtx1->m[1][0] + pMtx0->m[1][2] * pMtx1->m[2][0];
	concatMatrix.m[1][1] = pMtx0->m[1][0] * pMtx1->m[0][1] + pMtx0->m[1][1] * pMtx1->m[1][1] + pMtx0->m[1][2] * pMtx1->m[2][1];
	concatMatrix.m[1][2] = pMtx0->m[1][0] * pMtx1->m[0][2] + pMtx0->m[1][1] * pMtx1->m[1][2] + pMtx0->m[1][2] * pMtx1->m[2][2];

	concatMatrix.m[2][0] = pMtx0->m[2][0] * pMtx1->m[0][0] + pMtx0->m[2][1] * pMtx1->m[1][0] + pMtx0->m[2][2] * pMtx1->m[2][0];
	concatMatrix.m[2][1] = pMtx0->m[2][0] * pMtx1->m[0][1] + pMtx0->m[2][1] * pMtx1->m[1][1] + pMtx0->m[2][2] * pMtx1->m[2][1];
	concatMatrix.m[2][2] = pMtx0->m[2][0] * pMtx1->m[0][2] + pMtx0->m[2][1] * pMtx1->m[1][2] + pMtx0->m[2][2] * pMtx1->m[2][2];

	*pResult = concatMatrix;
}

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D* pResult, Matrix2D* pMtx0, Matrix2D* pMtx1)
{
	if (pResult == pMtx0 || pResult == pMtx1) {
		Matrix2D temp;
		Matrix2DConcatenationHelper(&temp, pMtx0, pMtx1);
		*pResult = temp;
	}
	else {
		Matrix2DConcatenationHelper(pResult, pMtx0, pMtx1);
	}
}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D* pResult, float x, float y)
{
	Matrix2D translateMatrix;
	Matrix2DIdentity(&translateMatrix);
	translateMatrix.m[0][2] = x;
	translateMatrix.m[1][2] = y;
	*pResult = translateMatrix;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D* pResult, float x, float y)
{
	Matrix2D scaleMatrix;
	Matrix2DIdentity(&scaleMatrix);
	scaleMatrix.m[0][0] = x;
	scaleMatrix.m[1][1] = y;
	*pResult = scaleMatrix;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D* pResult, float Angle)
{
	float angleInRadians = (float)(Angle * (PI / 180.0f));
	Matrix2DRotRad(pResult, angleInRadians);
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D* pResult, float Angle)
{
	Matrix2D rotionMatrix;
	Matrix2DIdentity(&rotionMatrix);

	float cosAngle = (float)cos(Angle);
	float sinAngle = (float)sin(Angle);

	rotionMatrix.m[0][0] = cosAngle;
	rotionMatrix.m[0][1] = -sinAngle;
	rotionMatrix.m[1][0] = sinAngle;
	rotionMatrix.m[1][1] = cosAngle;
	*pResult = rotionMatrix;
}

// ---------------------------------------------------------------------------

void Matrix2DVectorMultiplcationHelper(Vector2D* pResult, Matrix2D* pMtx, Vector2D* pVec) {
	pResult->x = pMtx->m[0][0] * pVec->x + pMtx->m[0][1] * pVec->y + pMtx->m[0][2];
	pResult->y = pMtx->m[1][0] * pVec->x + pMtx->m[1][1] * pVec->y + pMtx->m[1][2];
}

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D* pResult, Matrix2D* pMtx, Vector2D* pVec)
{
	if (pResult == pVec) {
		Vector2D temp;
		Matrix2DVectorMultiplcationHelper(&temp, pMtx, pVec);
		*pResult = temp;
	}
	else {
		Matrix2DVectorMultiplcationHelper(pResult, pMtx, pVec);
	}
}

// ---------------------------------------------------------------------------
