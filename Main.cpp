/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Main.cpp
Purpose: Main game loop
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

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Core.h"
#include "GameStateManager.h"
#include "GameState.h"

void InitializeWindow();
void FrameBufferSizeCallBack(GLFWwindow* window, GLsizei width, GLsizei height);

GLFWwindow* window;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

int main(int argc, char* args[])
{
	InitializeWindow();

	InitializeGameStateManager(GAME_STATE::GAME_INIT);
	//InitializeGameStateManager(GAME_STATE::GAME_ACTIVE);
	MainGameLoop();

	glfwTerminate();

	return 0;
}

void InitializeWindow() {
	if (!glfwInit()) {
		//std::cout << "Failed to initialize GLFW!!" << std::endl;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D PLATFORMER", NULL, NULL);
	if (window == NULL) {
		//std::cout << "Failed to create GLFW WINDOW!!" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		//std::cout << "Failed to initialize GLAD!!" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallBack);
}

void FrameBufferSizeCallBack(GLFWwindow* window, GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
}