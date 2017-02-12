#include "World.h"
#include "Model.h"
#include "Shader.h"
#include "GMath.h"
#include <stdio.h>

static Model model;
static Tilemap tilemap;
static GLuint bg;
static float* compMat4;
static float scale = 32.0f;
static float WIDTH, HEIGHT;
static float RATIO;

//load the game world
void loadWorld(float w, float h, Level lvl) {

	tilemap = lvl.map;
	bg = lvl.bg;
	WIDTH = w;
	HEIGHT = h;

	shaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	model = loadModel();

	RATIO = w/h;
	float* proj = loadOrtho(0.0, w*RATIO, 0.0, h*RATIO, -1.0f, 1.0f);

	bindShader();
	loadProjectionMatrix(proj);
	unBindShader();

	free(proj);
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

//prepare OpenGL before starting loop
void prepOGL() {

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	bindModel();
	bindShader();
}

//prepare to render something on da screen
void prepRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

//Render the world
void renderWorld() {

	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr,"OpenGL error: %d\n", err);
    }


	//backGround
	compMat4 = createMat4(NULL);
	loadIdentity(compMat4);
	glBindTexture(GL_TEXTURE_2D, bg);
	translateMat(compMat4, (Vec2D){(WIDTH/2)*RATIO, (HEIGHT/2)*RATIO});
	scale2DMat(compMat4,(Vec2D){(WIDTH/2)*RATIO, (HEIGHT/2)*RATIO} );
	loadCompositeMatrix(compMat4);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	//Render tilemap
	for(int i = 0; i < tilemap.nTiles; ++i) {

		loadIdentity(compMat4);

		glBindTexture(GL_TEXTURE_2D, tilemap.tiles[i].texture);

		translateMat(compMat4, (Vec2D){tilemap.tiles[i].pos.x * scale*2,
									   tilemap.tiles[i].pos.y * scale*2});
		scaleMat(compMat4, scale);
		loadCompositeMatrix(compMat4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

//cleanUp
void worldCleanUp() {
	unBindShader();
	unBindModel();
	free(compMat4);
	freeMap(&tilemap);
	shaderCleanUp();
}