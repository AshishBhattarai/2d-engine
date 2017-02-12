#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

typedef struct Model Model;

//Model
struct Model {
	GLuint vaoID;
	GLuint indiID;
};

//Loads model with a pre set coordinates
Model loadModel();


#endif