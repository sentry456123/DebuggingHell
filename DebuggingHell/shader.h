#pragma once

#include <iostream>

#include "gl.h"

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath) noexcept;

	inline ~Shader(void) noexcept
	{
		glDeleteProgram(mID);
	}

	inline void Use(void) noexcept
	{
		glUseProgram(mID);
	}

	inline void SetUniform(const char* name, float value) noexcept
	{
		int location = glGetUniformLocation(mID, name);
		if (location == -1) {
			std::cerr << "Failed to find uniform location \"" << name << "\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		glUniform1f(location, value);
	}

	inline void SetUniform(const char* name, const glm::vec2& value) noexcept
	{
		int location = glGetUniformLocation(mID, name);
		if (location == -1) {
			std::cerr << "Failed to find uniform location \"" << name << "\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		glUniform2f(location, value.x, value.y);
	}

	inline void SetUniform(const char* name, const glm::vec3& value) noexcept
	{
		int location = glGetUniformLocation(mID, name);
		if (location == -1) {
			std::cerr << "Failed to find uniform location \"" << name << "\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		glUniform3f(location, value.x, value.y, value.z);
	}

	inline void SetUniform(const char* name, const glm::vec4& value) noexcept
	{
		int location = glGetUniformLocation(mID, name);
		if (location == -1) {
			std::cerr << "Failed to find uniform location \"" << name << "\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	inline void SetUniform(const char* name, const glm::mat4& value) noexcept
	{
		int location = glGetUniformLocation(mID, name);
		if (location == -1) {
			std::cerr << "Failed to find uniform location \"" << name << "\"" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

protected:
	unsigned int mID;

};

