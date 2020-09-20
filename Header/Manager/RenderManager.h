#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Core.h"

class ShaderProgram;
class GameObject;
class Texture2D;

class RenderManager {

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	static glm::mat4 view;
	static const glm::mat4 projection;
	static const float vertices[48];
	static const unsigned int elements[6];
	

public:

	static bool useTexture;
	static bool debug;

	static int screenIndex;

	RenderManager(ShaderProgram* shaderProgram);
	~RenderManager();

	void Draw(ShaderProgram* shaderProgram, std::vector<GameObject*> mGameObjects);
	void DebugDraw(ShaderProgram* shaderProgram, std::vector<GameObject*> mGameObjects);
	void InitializeRenderingData(ShaderProgram* shaderProgram);
	void DrawTexture(ShaderProgram* shaderProgram, Texture2D* texture, glm::mat4& transform);

	static void ClampToViewPort(glm::vec3& value, glm::vec3& scale);
	static void UpdateCamera(glm::vec3& playerTransform);
	static void UpdateRenderScreen(int index);
};