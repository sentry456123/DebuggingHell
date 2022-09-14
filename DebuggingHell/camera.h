#pragma once

#include <cassert>

#include "gl.h"

class Camera
{
public:
	inline Camera(const glm::vec3& position, const glm::vec3& rotation, float fov, float sensitivity, float speed) noexcept
		:
		mPosition(position), mRotation(rotation), mUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		mYaw(-90.0f), mPitch(0.0f), mFov(fov), mRawSensitivity(sensitivity), mRawSpeed(speed)
	{
		assert(!singleton);
		singleton = this;
	}

	inline ~Camera(void) noexcept
	{
		singleton = nullptr;
	}

	void MousePositionCallback(double xpos, double ypos) noexcept;
	void ScrollCallback(double xoffset, double yoffset) noexcept;
	void ProcessInput(GLFWwindow* window) noexcept;
	inline glm::vec3 GetPosition(void) const noexcept { return mPosition; }
	inline glm::vec3 GetRotation(void) const noexcept { return mRotation; }
	inline glm::mat4 View(void) const noexcept
	{
		return glm::lookAt(mPosition, mPosition + mRotation, mUp);
	}
	inline float Fov(void) const noexcept { return mFov; }
	float Sensitivity(void) const noexcept;
	float Speed(void) const noexcept;

protected:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mUp;
	float mYaw;
	float mPitch;
	float mFov;
	float mRawSensitivity;
	float mRawSpeed;

public:
	static inline Camera* GetSingleton(void) noexcept
	{
		assert(singleton);
		return singleton;
	}

protected:
	static Camera* singleton;

};