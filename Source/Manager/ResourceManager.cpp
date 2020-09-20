/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ResourceManager.cpp
Purpose: Managing assets
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

#include "ResourceManager.h"
#include "Texture2D.h"
#include "stb_image.h"

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

Texture2D* ResourceManager::LoadTexture(const char* filePath, bool repeat) {
	Texture2D* texture = new Texture2D(0.0f, 0.0f, GL_RGBA, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	texture->Generate(width, height, data, repeat);
	stbi_image_free(data);
	return texture;
}