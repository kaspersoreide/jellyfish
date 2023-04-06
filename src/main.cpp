#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <iostream>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include "framebuffer.h"
#include "renderer.h"

#include "jellyfish.h"

using namespace glm;

GLFWwindow* window;
Renderer* renderer;
vec2 cameraAngles(0.0f, 0.0f);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch(key) {
	case  GLFW_KEY_LEFT: 
		if (action == GLFW_PRESS);
		if (action == GLFW_RELEASE);
		break;
	case  GLFW_KEY_RIGHT: 
		if (action == GLFW_PRESS);
		if (action == GLFW_RELEASE);
		break;
	case  GLFW_KEY_UP: 
		if (action == GLFW_PRESS);
		if (action == GLFW_RELEASE);
		break;
	case  GLFW_KEY_DOWN: 
		if (action == GLFW_PRESS);
		if (action == GLFW_RELEASE);
		break;
	case  GLFW_KEY_ESCAPE: 	//Disable fullscreen and close the application
		glfwSetWindowMonitor(
			window,
			NULL,
			40, 40,
			1280, 720, GLFW_DONT_CARE
		);
		glfwSetWindowShouldClose(window, 1);
		break;
	case GLFW_KEY_F: 	//Toggle fullscreen
		if (action == GLFW_PRESS) break;
		if (glfwGetWindowMonitor(window) == NULL) {
			glfwSetWindowMonitor(
				window,
				glfwGetPrimaryMonitor(),
				0, 0,
				1920, 1080, 30
			);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		} else {
			glfwSetWindowMonitor(
				window,
				NULL,
				40, 40,
				1280, 720, GLFW_DONT_CARE
			);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		
		break;
	default:
		break;
	}
}

void init() {
	glfwInit();
	window = glfwCreateWindow(1920, 1080, "<3", glfwGetPrimaryMonitor(), NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glfwSetKeyCallback(window, keyCallback);

	renderer = new Renderer();
}


int main() {
	init();

	Jellyfish jellyfish;

	glm::mat4 Projection = glm::perspective(
		1.2f,
		16.0f / 9,
		0.1f,
		100.0f
	);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0f, -5.0f, 0.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	glm::mat4 VP = Projection * View;

	while (!glfwWindowShouldClose(window)) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderer->buffers[0]->bind();
		renderer->renderJellyfish(&jellyfish, VP);
		renderer->renderToScreen();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}