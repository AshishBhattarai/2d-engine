#include "Display.h"
#include "Texture.h"
#include "World.h"
#include <stdio.h>

int main() {

	createDisplay(640, 480, "2D-Engine");

	GLuint texture = loadTexture("3.png");

	loadWorld();

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