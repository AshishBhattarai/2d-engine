#include "Display.h"
#include "Texture.h"
#include "World.h"
#include "Tilemap.h"
#include "Level.h"
#include "Entity.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720


void pMovement(Entity *player) {
	if(isKeyPressed(GLFW_KEY_W)) {
		player->pos.y += SPEED*getDelta();
	}

	if(isKeyPressed(GLFW_KEY_S)) {
		player->pos.y -= SPEED*getDelta();
	}

	if(isKeyPressed(GLFW_KEY_A)) {
		player->pos.x -= SPEED*getDelta();
	}

	if(isKeyPressed(GLFW_KEY_D)) {
		player->pos.x += SPEED*getDelta();
	}

	player->pos.x += 0;
	player->pos.y += 0;
}

int main() {

	createDisplay(WIDTH, HEIGHT, "2D-Engine");

	Level lvl1;
	lvl1.map = loadTiles("tilemap.png"); //t1 - 90 C-CW - Flip Horizontally - Flip V
	lvl1.bg = loadTexture("back.png");

	Entity player;
	player.pos.x = 0;
	player.pos.y = 0;

	loadWorld(WIDTH, HEIGHT, lvl1, &player);

	prepOGL();
	while(!shouldCloseWindow()) {
		startLoop();
		prepRender();
		renderWorld();
		pMovement(&player);

		//collision check
		int coll = tileCollision(player, lvl1.map);
		printf("%d\n", coll);
		endLoop();
	}

	worldCleanUp();
	displayCleanUp();
}