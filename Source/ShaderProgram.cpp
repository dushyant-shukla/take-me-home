#include "ShaderProgram.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram() {
	programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
}

unsigned int ShaderProgram::GetProgramId() {
	return programId;
}

char const* ShaderProgram::LoadShader(const std::string& filename) {
	/*std::ifstream file(filename);
	std::stringstream stream;
	stream << file.rdbuf();
	file.close();

	std::string code = stream.str();
	//std::cout << "Shader program: " << filename << std::endl << code << std::endl;
	return code.c_str();*/

	std::ifstream file;
	file.open(filename, std::ios_base::binary);
	file.seekg(0, std::ios_base::end);
	int length = file.tellg();

	char* code = new char[length + 1];
	file.seekg(0, std::ios_base::beg);
	file.read(code, length);
	code[length] = '\0';
	file.close();

	////std::cout << "Shader program: " << filename << std::endl << code << std::endl;
	return code;
}

void ShaderProgram::AddShader(const std::string& filename, unsigned int shaderType) {
	char const* code = LoadShader(filename);

	char const* source[] = { code };
	unsigned int shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, source, NULL);
	glCompileShader(shaderId);

	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		char informationLog[512];
		glGetShaderInfoLog(shaderId, 512, NULL, informationLog);
		//std::cout << "Shader compilation log::\nShader program::	" << filename << std::endl << informationLog << std::endl;
	}

	glAttachShader(programId, shaderId);
	glDeleteShader(shaderId);
}

void ShaderProgram::LinkProgram() {
	glLinkProgram(programId);
	int success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		char informationLog[512];
		glGetProgramInfoLog(programId, 512, NULL, informationLog);
		//std::cout << "Program linking log::\n" << informationLog << std::endl;
	}
}

void ShaderProgram::UseProgram() {
	glUseProgram(programId);
}

void ShaderProgram::UnuseProgram() {
	glUseProgram(0);
}

ShaderProgram* LoadShaderProgram(std::string vertexShader, std::string fragmentShader) {
	ShaderProgram* program = new ShaderProgram();
	program->AddShader(vertexShader, GL_VERTEX_SHADER);
	program->AddShader(fragmentShader, GL_FRAGMENT_SHADER);
	program->LinkProgram();
	return program;
}