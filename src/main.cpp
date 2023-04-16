#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <iostream>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include <chrono>

#include "jellyfish.h"
#include "renderer.h"

using namespace glm;

GLFWwindow* window;
Renderer* renderer;
struct {
	float theta, phi;
} cameraAngles;
struct {
	bool left, right, up, down;
} controller;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch(key) {
	case  GLFW_KEY_LEFT: 
		if (action == GLFW_PRESS) controller.left = true;
		if (action == GLFW_RELEASE) controller.left = false;
		break;
	case  GLFW_KEY_RIGHT: 
		if (action == GLFW_PRESS) controller.right = true;
		if (action == GLFW_RELEASE) controller.right = false;
		break;
	case  GLFW_KEY_UP: 
		if (action == GLFW_PRESS) controller.up = true;
		if (action == GLFW_RELEASE) controller.up = false;
		break;
	case  GLFW_KEY_DOWN: 
		if (action == GLFW_PRESS) controller.down = true;
		if (action == GLFW_RELEASE) controller.down = false;
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
	cameraAngles.phi = 3.1415926f / 2;
	cameraAngles.theta = 0.0f;
	controller.up = false;
	controller.down = false;
	controller.left = false;
	controller.right = false;
}

void moveCamera() {
	const float speed = 0.01f;
	if (controller.left) {
		cameraAngles.theta -= speed;
	}
	if (controller.right) {
		cameraAngles.theta += speed;
	}
	if (controller.up) {
		cameraAngles.phi += speed;
	}
	if (controller.down) {
		cameraAngles.phi -= speed;
	}
}

vec3 getCameraPos(float phi, float theta) {
	return {
		sinf(phi) * cosf(theta),
		sinf(phi) * sinf(theta),
		cosf(phi)
	};
}

int main() {
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();
    

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
		renderer->clear();
		auto t1 = Time::now();
    	fsec fs = t1 - t0;
		moveCamera();
		
		//cameraAngles.x += 0.001f;
		View = glm::lookAt(
			5.0f * getCameraPos(cameraAngles.phi, cameraAngles.theta),
			glm::vec3(0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		VP = Projection * View;

		renderer->renderJellyfish(&jellyfish, VP, fs.count());
		renderer->renderToScreen();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}