#include "window.h"

#include <iostream>
#include <cassert>

#include "camera.h"

static int currentWindowWidth;
static int currentWindowHeight;

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) noexcept
{
	glViewport(0, 0, width, height);
	currentWindowWidth = width;
	currentWindowHeight = height;
}

static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept
{
	Camera::GetSingleton()->MousePositionCallback(xpos, ypos);
}

static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept
{
	Camera::GetSingleton()->ScrollCallback(xoffset, yoffset);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

Window::Window(int width, int height, const char* title) noexcept
	:
	mDeltaTime(0.0f)
{
	assert(!singleton);
	singleton = this;

	currentWindowWidth = width;
	currentWindowHeight = height;

	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "GLFW initialization failed" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mGLFWWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!mGLFWWindow) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(mGLFWWindow);
	glfwSetFramebufferSizeCallback(mGLFWWindow, FrameBufferSizeCallback);
	glfwSetInputMode(mGLFWWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(mGLFWWindow, MousePositionCallback);
	glfwSetScrollCallback(mGLFWWindow, ScrollCallback);
	glfwSetKeyCallback(mGLFWWindow, KeyCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

Window::~Window(void) noexcept
{
	glfwTerminate();
	singleton = nullptr;
}

void Window::ProcessInput(void) noexcept
{
	Camera::GetSingleton()->ProcessInput(mGLFWWindow);
}

void Window::Update(void) noexcept
{
	static float lastFrame = 0.0f;
	float currentFrame = glfwGetTime();
	mDeltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	std::cout << "DeltaTime: " << mDeltaTime << std::endl;
}

void Window::SetScreenMode(ScreenMode mode) noexcept
{
	GLFWmonitor* monitor = nullptr;

	switch (mode) {
	case ScreenMode::WINDOWED:
		monitor = nullptr;
		break;
	case ScreenMode::BORDERLESS:
	case ScreenMode::FULLSCREEN:
		monitor = glfwGetPrimaryMonitor();
		break;
	}

	glfwSetWindowMonitor(mGLFWWindow, monitor, 0, 0, currentWindowWidth, currentWindowHeight, GLFW_DONT_CARE);
}

int Window::Width(void) const noexcept
{
	return currentWindowWidth;
}

int Window::Height(void) const noexcept
{
	return currentWindowHeight;
}

Window* Window::singleton = nullptr;