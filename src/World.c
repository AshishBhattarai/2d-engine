#include "World.h"
#include "Shader.h"
#include "Model.h"
#include "GMath.h"
#include <stdio.h>

static struct Model model;

//load the game world
void loadWorld(float w, float h) {

	shaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	model = loadModel();

	float* compMat4 = createMat4(NULL);
	loadIdentity(compMat4);
	scale(compMat4, 16.0f);
	translate(compMat4, (vec2D){2,1});

	float* proj = loadOrtho(0.0f, w, 0.0, h, -1.0f, 1.0f);
	bindShader();
	loadProjectionMatrix(proj);
	loadCompositeMatrix(compMat4);
	unBindShader();

	free(compMat4);
	free(proj);
}

//prepare OpenGL before starting loop
void prepOGL() {

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
}

//prepare to render something on da screen
void prepRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	bindShader();
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