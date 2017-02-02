#include "Display.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

static GLFWwindow* window;

//private functions
static void errorCallback(int error, const char* description) {
	fprintf(stderr, "Error: %s", description);
}

//public functions

//function create a display window
void createDisplay(int w, int h, const char* title) {

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
}

bool shouldCloseWindow() {
	return glfwWindowShouldClose(window);
}

void startLoop() {

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