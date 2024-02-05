#pragma once

#include "Graphics.h"
#include "glm.hpp"
#include <string>

class ShaderProgram
{
private:
	//Remember, OpenGL manages its resources itself and gives you handles to them.
	//That's what all this 'GLuint' business is about.
	GLuint vertexShader = -1;
	GLuint fragmentShader = -1;
	GLuint shaderProgram = -1;

	bool loadedSuccessfully = false;

public:
	ShaderProgram() {}
	ShaderProgram(std::string vertexFilename, std::string fragmentFilename);

	~ShaderProgram();

	//We don't want to be duplicating our shader around - that will screw us over.
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator= (const ShaderProgram& other) = delete;

	//Moving it around is fine though, we just have to do it properly.
	ShaderProgram(ShaderProgram&& other);
	ShaderProgram& operator= (ShaderProgram&& other);

	bool IsLoadedSuccessfully() const { return loadedSuccessfully; }

	void UseShader();

	GLuint GetUniformLocation(std::string varName);

	void SetUniform(std::string varName, float value);
	void SetUniform(std::string varName, glm::vec3 value);
	void SetUniform(std::string varName, glm::mat4 value);
};
