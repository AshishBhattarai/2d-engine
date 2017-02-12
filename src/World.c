#include "World.h"
#include "Model.h"
#include "Shader.h"
#include "GMath.h"
#include <stdio.h>

static Model model;
static Tilemap tilemap;
static float* compMat4;
static float scale = 32.0f;
static int HEIGHT, WIDTH;

//load the game world
void loadWorld(float w, float h, Tilemap map) {

	HEIGHT = h;
	WIDTH = w;
	tilemap = map;

	shaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	model = loadModel();

	float* proj = loadOrtho(0.0f, w, 0.0, h, -1.0f, 1.0f);
	bindShader();
	loadProjectionMatrix(proj);
	unBindShader();

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
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	bindShader();
}

void bindModel() {
	glBindVertexArray(model.vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.indiID);

}

void unBindModel() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

//Render the world
void renderWorld() {

	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr,"OpenGL error: %d\n", err);
    }

	bindModel();

	//Render tilemap
	for(int i = 0; i < tilemap.nTiles; ++i) {
		compMat4 = createMat4(NULL);
		loadIdentity(compMat4);

		//Calculate Scale according to resolution
		float viewX = (float)(WIDTH)/(scale);
		float viewY = (float)(HEIGHT)/(scale);
		translateMat(compMat4, (Vec2D){tilemap.tiles[i].pos.x * viewX,
									   tilemap.tiles[i].pos.y * viewY});
		scaleMat(compMat4, scale);
		loadCompositeMatrix(compMat4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}

	unBindModel();
}

//cleanUp
void worldCleanUp() {
	free(compMat4);
	freeMap(&tilemap);
	shaderCleanUp();
}