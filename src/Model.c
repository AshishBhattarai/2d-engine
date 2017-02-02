#include "Model.h"


struct Model loadModel(float* vertices, float* texCoords, int* indices) {
	//VBOs
	GLuint vID = 0;
	GLuint tID = 0;
	GLuint iID = 0;
	//VAO
	GLuint vaoID = 0;

	//load vertex coords to vbo
	glGenBuffers(1, &vID);
	glBindBuffer(GL_ARRAY_BUFFER, vID);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), vertices, GL_STATIC_DRAW);

	//load texture coords to vbo
	glGenBuffers(1, &tID);
	glBindBuffer(GL_ARRAY_BUFFER, tID);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), texCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//load indices to vbo
	glGenBuffers(1, &iID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//load vertex&texture vbo to VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, tID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	struct Model model;
	model.vaoID = vaoID;
	model.indiID = iID;

	return model;
}

