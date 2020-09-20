/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture2D.h
Purpose: Skeleton for Texture2D.cpp
Language: C/C++ using Visual Studio 2019
Platform: Visual Studio 2019,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
					Windows 7 SP 2

Project: 		CS529_dushyant.shukla_FinalProject_Milestone1

Author: Name: Dushyant Shukla ;  Login: dushyant.shukla  ; Student ID : 60000519
Creation date: October 16, 2019.
- End Header --------------------------------------------------------*/

#pragma once

#include <glad/glad.h>

class Texture2D {

public:

	Texture2D();
	Texture2D(GLfloat width, GLfloat height, GLuint internalFormat, GLuint imageFormat, GLuint wrapS, GLuint wrapT, GLuint filterMin, GLuint filterMax);
	~Texture2D();

	GLuint id;
	GLfloat height;
	GLfloat width;
	GLuint internalFormat; // Format of texture object
	GLuint imageFormat; // Format of loaded image

	GLuint wrapS; // Wrapping mode on S axis
	GLuint wrapT; // Wrapping mode on T axis
	GLuint filterMin; // Filtering mode if texture pixels < screen pixels
	GLuint filterMax; // Filtering mode if texture pixels > screen pixels

	void Generate(GLuint width, GLuint height, unsigned char* data, bool repeat);
	void Bind() const;
	void Unbind() const;
};
