#include "Display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static GLFWwindow* window;
char* wTitle;
static int fpsCnt =0, lastCount = 0;
static int lastFrame, delta = 0;

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
void createDisplay(int w, int h, const char* title) {
	wTitle = strdup(title);
	glfwSetErrorCallback(errorCallback);
	if(!glfwInit()) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//OGL version - 3.2
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

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
}

bool shouldCloseWindow() {
	return glfwWindowShouldClose(window);
}

void startLoop() {
	calcFps();
	calcDelta();
}

int getDelta() {
	return delta;
}

void endLoop() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void cleanUp() {
	glfwDestroyWindow(window);
	glfwTerminate();
	fprintf(stdout, "Window destroyed.");
	exit(EXIT_SUCCESS);
}