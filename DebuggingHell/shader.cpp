#include "shader.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "fs.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) noexcept
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	std::string vertexShaderSource = FileSystem::ReadFile(vertexShaderPath);
	const char* vertexShaderSourcePtr = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "Vertex shader compilation error:" << std::endl << infoLog << std::endl;
		std::exit(EXIT_FAILURE);
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string fragmentShaderSource = FileSystem::ReadFile(fragmentShaderPath);
	const char* fragmentShaderSourcePtr = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "Fragment shader compilation error:" << std::endl << infoLog << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mID = glCreateProgram();
	glAttachShader(mID, vertexShader);
	glAttachShader(mID, fragmentShader);
	glLinkProgram(mID);

	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(mID, 512, nullptr, infoLog);
		std::cerr << "Shader program linking error:" << std::endl << infoLog << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
