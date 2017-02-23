#include "Model.h"


Model loadModel() {

	float vertices[] = {
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		 2.0f, 0.0f, 0.0f,
		 2.0f, 2.0f, 0.0f
	};

	float texCoords[] = {
		0,0,
		0,1,
		1,1,
		1,0
	};

	float texCoords2[] = {
		1,0,
		1,1,
		0,1,
		0,0
	};

	int indices[] = {
		0,1,2,
		2,3,0
	};

	//VBOs
	GLuint vID = 0;
	GLuint tID = 0;
	GLuint t2ID = 0;
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

	glGenBuffers(1, &t2ID);
	glBindBuffer(GL_ARRAY_BUFFER, t2ID);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), texCoords2, GL_STATIC_DRAW);
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

	glBindBuffer(GL_ARRAY_BUFFER, t2ID);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Model model;
	model.vaoID = vaoID;
	model.indiID = iID;

	return model;
}
