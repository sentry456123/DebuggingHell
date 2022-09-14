#pragma once

#include <cassert>

#include "gl.h"

class Window;

class Mouse
{
public:
	enum class Button
	{
		LEFT = GLFW_MOUSE_BUTTON_LEFT,
		RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
		MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
	};

public:
	inline Mouse(Window* window) noexcept
		:
		mWindow(window), mFocused(true)
	{
		assert(!singleton);
		singleton = this;
	}

	inline ~Mouse(void) noexcept
	{
		singleton = nullptr;
	}

	bool IsPressed(Mouse::Button button) noexcept;
	glm::f64vec2 GetPosition(void) noexcept;

	inline bool IsFocused(void) const noexcept { return mFocused; }
	inline void SetFocused(bool focused) noexcept { mFocused = focused; }

protected:
	Window* mWindow;
	bool mFocused;

public:
	static inline Mouse* GetSingleton(void) noexcept
	{
		assert(singleton);
		return singleton;
	}

protected:
	static Mouse* singleton;

};