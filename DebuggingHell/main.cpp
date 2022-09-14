#include "gl.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>

#include "window.h"
#include "fs.h"
#include "shader.h"
#include "keyboard.h"
#include "mouse.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"

#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720
#define TITLE "Debugging Hell"

static Window* window = nullptr;
static Keyboard* keyboard = nullptr;
static Mouse* mouse = nullptr;
static Camera* camera = nullptr;

int main(int argc, char** argv) noexcept
{
	window = new Window(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, TITLE);
	keyboard = new Keyboard(window);
	mouse = new Mouse(window);
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 2.0f, 2.0f);

	constexpr std::size_t verticesLen = 20;
	float* vertices = new float[verticesLen] {
		 1.0f,  1.0f,  0.0f,  2.0f,  2.0f,
		 1.0f, -1.0f,  0.0f,  2.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  0.0f,  0.0f,  2.0f,
	}; 

	constexpr std::size_t indicesLen = 6;
	unsigned int* indices = new unsigned int[indicesLen] {
		0, 1, 3,
		1, 2, 3,
	};

	Shader shader("res/shaders/vert.glsl", "res/shaders/frag.glsl");

	Mesh mesh(DynamicArray<float>(vertices, verticesLen), DynamicArray<unsigned int>(indices, indicesLen));

	Texture texture("res/textures/awesome.png");

	while (!Window::GetSingleton()->ShouldClose()) {
		Window::GetSingleton()->ProcessInput();

		Window::GetSingleton()->Update();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;
		view = Camera::GetSingleton()->View();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(Camera::GetSingleton()->Fov()), (float)Window::GetSingleton()->Width() / (float)Window::GetSingleton()->Height(), 0.1f, 1000.0f);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3((float)texture.Width() / (float)texture.Height(), 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(10.0f));

		shader.Use();
		shader.SetUniform("view", view);
		shader.SetUniform("projection", projection);
		shader.SetUniform("model", model);

		texture.Bind();
		mesh.Bind();

		mesh.Draw();

		Window::GetSingleton()->SwapBuffers();
		Window::GetSingleton()->PollEvents();
	}

	delete keyboard;
	delete mouse;
	delete camera;
	delete window;

	return 0;
}