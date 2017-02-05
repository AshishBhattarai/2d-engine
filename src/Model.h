#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

//Model
struct Model {
	GLuint vaoID;
	GLuint indiID;
};

//Loads model with a pre set coordinates
struct Model loadModel();

//Renders the given model
void renderModel(struct Model);

#endif