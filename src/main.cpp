#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <iostream>
#include <GL/glew.h>
#include "glm/ext.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/quaternion.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

GLFWwindow* window;

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
		} else {
			glfwSetWindowMonitor(
				window,
				NULL,
				40, 40,
				1280, 720, GLFW_DONT_CARE
			);
		}
		
		break;
	default:
		break;
	}
}

void init() {
	glfwInit();
	window = glfwCreateWindow(1280, 720, "<3", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glfwSetKeyCallback(window, keyCallback);
}


int main() {
	init();

	glm::mat4 Projection = glm::perspective(
		1.2f,
		16.0f / 9,
		0.1f,
		100.0f
	);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	glm::mat4 VP = Projection * View;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}