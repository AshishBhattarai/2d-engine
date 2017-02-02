#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

//Model
struct Model {
	GLuint vaoID;
	GLuint indiID;
};

//takes model coors loads it and returns Model
struct Model loadModel(float* vertices, float* text_coords, int* indices);


#endif