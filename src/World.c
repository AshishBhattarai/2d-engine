#include "World.h"
#include "Shader.h"
#include "Model.h"
#include <stdio.h>

static struct Model model;

//load the game world
void loadWorld() {

	shaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	model = loadModel();
}

//prepare OpenGL before starting loop
void prepOGL() {

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

//prepare to render something on da screen
void prepRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	useShader();
}

//Render the world
void renderWorld() {

	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr,"OpenGL error: %d\n", err);
    }
	renderModel(model);
}

//cleanUp
void worldCleanUp() {
	shaderCleanUp();
}