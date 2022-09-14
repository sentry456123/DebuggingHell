#include "camera.h"

#include "mouse.h"
#include "keyboard.h"
#include "window.h"

void Camera::MousePositionCallback(double xpos, double ypos) noexcept
{
	if (!Mouse::GetSingleton()->IsFocused()) {
		return;
	}

	static float lastx = (float)xpos;
	static float lasty = (float)ypos;

	float xoffset = (float)xpos - lastx;
	float yoffset = lasty - (float)ypos;

	lastx = (float)xpos;
	lasty = (float)ypos;

	xoffset *= Sensitivity();
	yoffset *= Sensitivity();

	mYaw += xoffset;
	mPitch += yoffset;

	if (mPitch > 89.0f)
		mPitch = 89.0f;
	else if (mPitch < -89.0f)
		mPitch = -89.0f;

	glm::vec3 direction = {};
	direction.x = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
	direction.y = glm::sin(glm::radians(mPitch));
	direction.z = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
	mRotation = glm::normalize(direction);
}

void Camera::ScrollCallback(double xoffset, double yoffset) noexcept
{
	mFov -= (float)yoffset * 4;
	if (mFov < 10.0f)
		mFov = 10.0f;
	else if (mFov > 90.0f)
		mFov = 90.0f;
}

void Camera::ProcessInput(GLFWwindow* window) noexcept
{
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::ESCAPE)) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		Mouse::GetSingleton()->SetFocused(false);
	}
	if (Mouse::GetSingleton()->IsPressed(Mouse::Button::LEFT)) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		Mouse::GetSingleton()->SetFocused(true);
	}
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::W))
		mPosition += Speed() * mRotation;
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::S))
		mPosition -= Speed() * mRotation;
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::A))
		mPosition -= glm::normalize(glm::cross(mRotation, mUp)) * Speed();
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::D))
		mPosition += glm::normalize(glm::cross(mRotation, mUp)) * Speed();
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::Q))
		mPosition.y += Speed();
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::E))
		mPosition.y -= Speed();
	if (Keyboard::GetSingleton()->IsPressed(Keyboard::Key::LEFT_CONTROL) && Keyboard::GetSingleton()->IsPressed(Keyboard::Key::W))
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

float Camera::Sensitivity(void) const noexcept
{
	return mRawSensitivity * Window::GetSingleton()->DeltaTime() * 2.0f;
}

float Camera::Speed(void) const noexcept
{
	return mRawSpeed * Window::GetSingleton()->DeltaTime() * 10.0f;
}

Camera* Camera::singleton = nullptr;