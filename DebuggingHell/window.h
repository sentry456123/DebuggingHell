#pragma once

#include "gl.h"

enum class ScreenMode
{
	WINDOWED,
	BORDERLESS,
	FULLSCREEN,
};

class Window
{
public:
	Window(int width, int height, const char* title) noexcept;
	~Window(void) noexcept;
	
	void ProcessInput(void) noexcept;
	void Update(void) noexcept;
	void SetScreenMode(ScreenMode mode) noexcept;
	int Width(void) const noexcept;
	int Height(void) const noexcept;

	inline bool ShouldClose(void) const noexcept
	{
		return glfwWindowShouldClose(mGLFWWindow);
	}

	inline void PollEvents(void) noexcept
	{
		glfwPollEvents();
	}

	inline void SwapBuffers(void) noexcept
	{
		glfwSwapBuffers(mGLFWWindow);
	}

	inline GLFWwindow* GetGLFWWindow(void) noexcept { return mGLFWWindow; }
	inline float DeltaTime(void) const noexcept { return mDeltaTime; }

protected:
	GLFWwindow* mGLFWWindow;
	float mDeltaTime;

public:
	static inline Window* GetSingleton(void) noexcept { return singleton; }

protected:
	static Window* singleton;

};