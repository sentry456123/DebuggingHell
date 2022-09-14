#include "keyboard.h"

#include "window.h"

Keyboard* Keyboard::singleton = nullptr;

bool Keyboard::IsPressed(Key key) const noexcept
{
	return glfwGetKey(mWindow->GetGLFWWindow(), (int)key) == GLFW_PRESS;
}