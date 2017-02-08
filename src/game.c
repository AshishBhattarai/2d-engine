#include "Display.h"
#include "Texture.h"
#include "World.h"
#include <stdio.h>

int main() {

	int width = 800, height = 600;

	createDisplay(width, height, "2D-Engine");

	GLuint texture = loadTexture("3.png");

	loadWorld(width, height);

	prepOGL();
	while(!shouldCloseWindow()) {
		startLoop();

		prepRender();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		renderWorld();

		endLoop();
	}

	worldCleanUp();
	displayCleanUp();
}