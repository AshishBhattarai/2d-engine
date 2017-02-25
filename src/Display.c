#include "Display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static GLFWwindow* window;
static char* wTitle;
static int fpsCnt = 0, lastFrame = 0;
static float lastCount = 0, delta = 0;

//private functions
static void errorCallback(int error, const char* description) {
	fprintf(stderr, "Error: %s", description);
}

static void calcFps() {
	if(glfwGetTime() - lastFrame > 1) {
		char sFps[4];
		sprintf(sFps, "%d ", fpsCnt);
		glfwSetWindowTitle(window, strcat(sFps, wTitle));
		fpsCnt = 0;
		lastFrame = glfwGetTime();
	}
	++fpsCnt;
}

static void calcDelta() {
	delta = (glfwGetTime()*1000-lastCount);
	lastCount = glfwGetTime()*1000;
}

//public functions

//function create a display window
void createDisplay(int w, int h, char* title) {
	wTitle = title;
	glfwSetErrorCallback(errorCallback);
	if(!glfwInit()) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//OGL version - 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//creating window
	window = glfwCreateWindow(w, h, title, NULL, NULL);
	if(!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	GLuint err = glewInit();
	if(err != GLEW_OK) {
		fprintf(stderr, "Error %s", glewGetErrorString(err));
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
}

bool shouldCloseWindow() {
	return glfwWindowShouldClose(window);
}

void startLoop() {
	calcFps();
	calcDelta();
}

float getDelta() {
	return delta;
}

void endLoop() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool isKeyPressed(int key) {
	return glfwGetKey(window, key);
}

void displayCleanUp() {
	glfwDestroyWindow(window);
	glfwTerminate();
	fprintf(stdout, "Window destroyed.");
	exit(EXIT_SUCCESS);
}