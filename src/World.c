#include "World.h"
#include "Model.h"
#include "Shader.h"
#include "GMath.h"
#include "Entity.h"
#include <stdio.h>

static Model model;
static float* compMat4;
static float scale = TILE_SIZE/2;
static float WIDTH, HEIGHT;
static float RATIO;
static Vec2D camera;
Entity *Player;

//load the game world
void loadWorld(float w, float h, Entity *player) {

	WIDTH = w;
	HEIGHT = h;
	Player = player;

	model = loadModel();
	shaders("shaders/vertex.glsl", "shaders/fragment.glsl");

	RATIO = w/h;
	float* proj = loadOrtho(0.0, w, 0.0, h, -1.0f, 1.0f);

	bindShader();
	loadProjectionMatrix(proj);
	unBindShader();

	free(proj);
}

void updateCamera() {
	loadIdentity(compMat4);

	if(Player->pos.x >= WIDTH/2) {
		camera.x = (Player->pos.x-WIDTH/2);
		translateMat(compMat4, (Vec2D){-camera.x, 0.0});
	}

	if(Player->pos.y >= HEIGHT/2) {
		camera.y = (Player->pos.y-HEIGHT/2);
		translateMat(compMat4, (Vec2D){0.0, -camera.y});
	}

	loadViewMatrix(compMat4);
}

void bindModel() {
	glBindVertexArray(model.vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.indiID);

}

void unBindModel() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

//prepare OpenGL before starting loop
void prepOGL() {

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	bindModel();
	bindShader();
}

//prepare to render something on da screen
void prepRender() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawBackground(GLuint bg) {
	//backGround
	compMat4 = createMat4(NULL);
	loadIdentity(compMat4);
	loadViewMatrix(compMat4);
	glBindTexture(GL_TEXTURE_2D, bg);
	//translateMat(compMat4, (Vec2D){(0), (0)});
	scale2DMat(compMat4,(Vec2D){(WIDTH/2), (HEIGHT/2)} );
	loadCompositeMatrix(compMat4);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void drawMap(Tilemap tilemap) {
	//Render tilemap
	for(int i = 0; i < tilemap.nTiles; ++i) {

		loadIdentity(compMat4);
		translateMat(compMat4, (Vec2D){tilemap.tiles[i].pos.x,
									   tilemap.tiles[i].pos.y});
		if(!tilemap.tiles[i].animate) {
			glBindTexture(GL_TEXTURE_2D, tilemap.spriteSheet.texture);
			loadSpriteSize(tilemap.spriteSheet.spriteSize);
			loadFrame(getSprite(tilemap.spriteSheet, tilemap.tiles[i].sprite.x,
								tilemap.tiles[i].sprite.y));
			scaleMat(compMat4, scale);
		} else {
			glBindTexture(GL_TEXTURE_2D,
						  tilemap.tiles[i].animation.spriteSheet.texture);
			loadSpriteSize(tilemap.tiles[i].animation.spriteSheet.spriteSize);
			animate(&tilemap.tiles[i].animation);
			loadFrame(tilemap.tiles[i].animation.frame);
			scaleMat(compMat4, scale/2);
		}

		loadCompositeMatrix(compMat4);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void drawEntitiy(Entity *entity) {
	loadIdentity(compMat4);
	translateMat(compMat4, (Vec2D){entity->pos.x, entity->pos.y});
	scaleMat(compMat4, scale);
	loadCompositeMatrix(compMat4);
	glBindTexture(GL_TEXTURE_2D, entity->animation.spriteSheet.texture);
	setFacing(entity->facing);

	//sprite sheet animation
	animate(&entity->animation);
	loadFrame(entity->animation.frame);
	loadSpriteSize(entity->animation.spriteSheet.spriteSize);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void drawEntities(Enemy *enemies, int nEnemies) {

	for(int i =0; i < nEnemies; ++i)
		drawEntitiy(&enemies[i].entity);

	drawEntitiy(Player);
}

//Render the world
void renderWorld(Level *lvl) {
	setFacing(true); //texture facing false - back -- true - front
	loadFrame((Vec2D){0, 0});
	loadSpriteSize((Vec2D){1, 1});

	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr,"OpenGL error: %d\n", err);
    }

	drawBackground(lvl->bg);

	updateCamera();

	drawMap(lvl->map);

	drawEntities(lvl->enemies, lvl->nEnemies);
}

//cleanUp
void worldCleanUp() {
	unBindShader();
	unBindModel();
	free(compMat4);
	shaderCleanUp();
	fprintf(stderr,"World Destroyed.\n");
}