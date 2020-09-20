#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 inTextureCoordinate;
layout (location = 0) in vec3 inColor;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 modelViewProjection;

out vec2 textureCoordinates;
out vec3 outColor;

void main() {
	outColor = inColor;
	textureCoordinates = inTextureCoordinate;
	//gl_Position = projection * model * vec4(position, 1.0f);
	gl_Position = projection * view * model * vec4(position, 1.0f);
}