#include "mouse.h"

#include "window.h"

bool Mouse::IsPressed(Mouse::Button button) noexcept
{
	return glfwGetMouseButton(mWindow->GetGLFWWindow(), (int)button) == GLFW_PRESS;
}

glm::f64vec2 Mouse::GetPosition(void) noexcept
{
	glm::f64 x, y;
	glfwGetCursorPos(mWindow->GetGLFWWindow(), &x, &y);
	return glm::f64vec2(x, y);
}

Mouse* Mouse::singleton = nullptr;
