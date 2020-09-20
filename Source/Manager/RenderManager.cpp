/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: RenderManager.cpp
Purpose: Rendering objects on screen
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

#include "RenderManager.h"
#include "ShaderProgram.h"

#include "TileType.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "Transform.h"
#include "Body.h"
#include "Sprite.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

extern GameObjectManager* gameObjectManager;

RenderManager::RenderManager(ShaderProgram* shaderProgram) {
	InitializeRenderingData(shaderProgram);
	view = glm::mat4(1.0f);
}

RenderManager::~RenderManager() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

bool RenderManager::useTexture = true;
bool RenderManager::debug = false;
int RenderManager::screenIndex = 0;

glm::mat4 RenderManager::view = glm::mat4(1.0);

glm::mat4 const RenderManager::projection = glm::ortho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);

GLfloat const RenderManager::vertices[] = {

	 // correct
	 0.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
	 1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	 0.0f,  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
	 1.0f,  1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f

};

GLuint const RenderManager::elements[] = {
	0, 1, 2,
	0, 3, 1
};

void RenderManager::InitializeRenderingData(ShaderProgram* shaderProgram) {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RenderManager::vertices), RenderManager::vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(RenderManager::elements), RenderManager::elements, GL_STATIC_DRAW);

	GLuint attributeLocation = glGetAttribLocation(shaderProgram->GetProgramId(), "position");
	glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(attributeLocation);

	attributeLocation = glGetAttribLocation(shaderProgram->GetProgramId(), "inColor");
	glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(attributeLocation);

	attributeLocation = glGetAttribLocation(shaderProgram->GetProgramId(), "inTextureCoordinate");
	glVertexAttribPointer(attributeLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(attributeLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void RenderManager::Draw(ShaderProgram* shaderProgram, std::vector<GameObject*> mGameObjects) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shaderProgram->UseProgram();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	for (GameObject* gameObject : mGameObjects) {
		Transform* pTransform = static_cast<Transform*> (gameObject->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		Sprite* pSprite = static_cast<Sprite*> (gameObject->GetComponent(COMPONENT_TYPE::COMPONENT_SPRITE));

		if (pSprite != nullptr && pTransform != nullptr) {
			Texture2D* texture = pSprite->GetTexture();
			glActiveTexture(GL_TEXTURE0);
			texture->Bind();

			GLuint attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "model");
			glUniformMatrix4fv(attributeLocation, 1, GL_FALSE, glm::value_ptr(pTransform->getTransform()));

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "projection");
			glUniformMatrix4fv(attributeLocation, 1, GL_FALSE, glm::value_ptr(RenderManager::projection));

			//view = glm::mat4(1.0f);
			//if (pTransform->GetPosition().x >= (2 * 1000.0 /3 )) {
			//	view = glm::translate(view, glm::vec3(-15.0f, 0.0f, 0.0f));
			//}
			//view = glm::translate(view, glm::vec3(-5.0f, 0.0f, 0.0f));
			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "view");
			glUniformMatrix4fv(attributeLocation, 1, GL_FALSE, glm::value_ptr(RenderManager::view));

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "useTexture");
			glUniform1i(attributeLocation, useTexture);

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "debug");
			glUniform1i(attributeLocation, debug);

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "useColor");
			glUniform1i(attributeLocation, true);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			texture->Unbind();
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
}

void RenderManager::DebugDraw(ShaderProgram* shaderProgram, std::vector<GameObject*> mGameObjects) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shaderProgram->UseProgram();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	for (GameObject* gameObject : mGameObjects) {

		Transform* pTransform = static_cast<Transform*> (gameObject->GetComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		Body* pBody = static_cast<Body*> (gameObject->GetComponent(COMPONENT_TYPE::COMPONENT_BODY));

		if (pBody != nullptr && pTransform != nullptr) {

			glm::mat4 transform = glm::mat4(1.0f);
			if (pBody->GetShape()->GetType() == Shape::SHAPE_TYPE::RECTANGLE) {
				ShapeAABB* rectangle = (ShapeAABB*)pBody->GetShape();

				if (pBody->GetOwner()->GetType() == GameObjectUtility::OBJECT_TYPE::PLAYER) {
					
					if (pBody->GetCurrentState() == GameObjectUtility::CHARACTER_STATE::WALK) {
						int a = 10;
						int b = a;
					}

					glm::vec3 scale = rectangle->GetSize();
					float x = scale.x;
					float posX = rectangle->GetCenter().x;
					float rotationAngle = -270;
					if (pBody->IsFacingLeft()) {
						rotationAngle = -rotationAngle;
						x = -x;
						posX = posX + scale.x;
					}

					if (pBody->GetCurrentState() == GameObjectUtility::CHARACTER_STATE::STAND) {
						rotationAngle = 0.0f;
					}
					else if (pBody->GetCurrentState() == GameObjectUtility::CHARACTER_STATE::JUMP) {
						if (rotationAngle < 0) {
							rotationAngle += 0.5;
						}
						else {
							rotationAngle -= 0.5;
						}
					}

					//glm::mat4 Transform = glm::mat4(1.0f);
					transform = glm::translate(transform, glm::vec3(posX - rectangle->GetHalfSize().x, rectangle->GetCenter().y - rectangle->GetHalfSize().y, 0.0f));

					transform = glm::translate(transform, glm::vec3(0.5f * x, 0.5f * scale.y, 0.0f));
					transform = glm::rotate(transform, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
					transform = glm::translate(transform, glm::vec3(-0.5f * x, -0.5f * scale.y, 0.0f));

					/*if (mVelocity.x < 0.0f) {
						scale.x = -scale.x;
					}*/
					transform = glm::scale(transform, glm::vec3(x, scale.y, 0.0f)); // change this to use scale

				}
				else {
					
					transform = glm::translate(transform, glm::vec3(rectangle->GetCenter().x - rectangle->GetHalfSize().x, rectangle->GetCenter().y - rectangle->GetHalfSize().y, 0.0f));
					transform = glm::scale(transform, rectangle->GetSize());
				}
			}
			else if (pBody->GetShape()->GetType() == Shape::SHAPE_TYPE::CIRCLE) {
				ShapeCircle* circle = (ShapeCircle*)pBody->GetShape();
				transform = glm::translate(transform, glm::vec3(circle->GetCenter().x - circle->GetRadius(), circle->GetCenter().y - circle->GetRadius(), 0.0f));
				transform = glm::scale(transform, glm::vec3(circle->GetRadius() * 2, circle->GetRadius() * 2, 1.0f));
			}

			GLuint attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "model");
			glUniformMatrix4fv(attributeLocation, 1, GL_FALSE, glm::value_ptr(transform));

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "projection");
			glUniformMatrix4fv(attributeLocation, 1, GL_FALSE, glm::value_ptr(RenderManager::projection));

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "useTexture");
			glUniform1i(attributeLocation, false);

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "debug");
			glUniform1i(attributeLocation, debug);

			attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "useColor");
			glUniform1i(attributeLocation, false);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_, 0, 4);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RenderManager::DrawTexture(ShaderProgram* shaderProgram, Texture2D* texture, glm::mat4& transform) {
	shaderProgram->UseProgram();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	texture->Bind();

	GLuint attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "model");
	glUniformMatrix4fv(attributeLocation, 1, GL_FALSE, glm::value_ptr(transform));

	attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "projection");
	glUniformMatrix4fv(attributeLocation, 1, GL_FALSE, glm::value_ptr(RenderManager::projection));

	attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "useTexture");
	glUniform1i(attributeLocation, useTexture);

	attributeLocation = glGetUniformLocation(shaderProgram->GetProgramId(), "useColor");
	glUniform1i(attributeLocation, true);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	texture->Unbind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void RenderManager::ClampToViewPort(glm::vec3& value, glm::vec3& scale) {
	if (value.x < 0.0f) {
		value.x = value.x > 0.0f ? value.x : 0.0f;
		value.x = (value.x + scale.x) < SCREEN_WIDTH ? value.x : SCREEN_WIDTH - scale.x;
	}
	else if (value.x + scale.x >= TILE_SIZE* MAP_WIDTH) {
		value.x = TILE_SIZE * MAP_WIDTH - scale.x;
	}
}

void RenderManager::UpdateCamera(glm::vec3& playerPosition) {
	view = glm::mat4(1.0f);

	float changeInHorizontalDirection = SCREEN_WIDTH / 2 - playerPosition.x;
	if (changeInHorizontalDirection > 0.0f) {
		changeInHorizontalDirection = 0.0f;
	}

	if (playerPosition.x + SCREEN_WIDTH / 2 >= MAP_WIDTH * TILE_SIZE) {
		changeInHorizontalDirection = SCREEN_WIDTH - MAP_WIDTH * TILE_SIZE;
	}
	
	view = glm::translate(view, glm::vec3(changeInHorizontalDirection, 0.0f, 0.0f));
}

void RenderManager::UpdateRenderScreen(int index) {
	screenIndex = index;
}
