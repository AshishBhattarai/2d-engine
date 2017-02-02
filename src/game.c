#include "Display.h"
#include "Model.h"
#include "Texture.h"
#include <stdio.h>

int main() {

	createDisplay(640, 480, "2D-Engine");

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f
	};

	float textCorrds[] = {
		0,0,
		0,1,
		1,1,
		1,0
	};

	int indices[] = {
		0,1,2,
		2,3,0
	};

	GLuint texture = loadTexture("pirate.png");

	struct Model model = loadModel(vertices, textCorrds, indices);

	glEnable(GL_TEXTURE_2D);

	while(!shouldCloseWindow()) {
		startLoop();

		//prepare to render
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 0, 0, 1);

		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(model.vaoID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.indiID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		endLoop();
	}

	cleanUp();
}