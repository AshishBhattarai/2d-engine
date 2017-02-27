#include "Display.h"
#include "SpriteSheet.h"
#include "World.h"
#include "Level.h"
#include "Tilemap.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

Vec2D movement;

static int oldState = GLFW_RELEASE;

void pMovement(Entity *player, Tilemap map) {

	player->animation.state = IDEL;

	if(isKeyPressed(GLFW_KEY_W) && oldState == GLFW_RELEASE) {
		if(player->canjump) {
			movement.y += JUMP;
			player->canjump = 0;
		}
	}
	oldState = isKeyPressed(GLFW_KEY_W);

	if(isKeyPressed(GLFW_KEY_S)) {
		// movement.y -= SPEED;
	}

	if(isKeyPressed(GLFW_KEY_A)) {

		movement.x -= SPEED;
		player->facing = false;
		player->animation.state = WALKING;
	}

	if(isKeyPressed(GLFW_KEY_D)) {
		movement.x += SPEED;
		player->facing = true;
		player->animation.state = WALKING;
	}

	moveEntity(&movement, player, map, getDelta());
}


int main() {

	createDisplay(WIDTH, HEIGHT, "2D-Engine");

	Level lvl1;
	SpriteSheet tileSheet = loadSpriteSheet("tilesheet.png", (Vec2D){64,64},
											(Vec2D){128,64});
	//t1 - 90 C-CW - Flip Horizontally - Flip V
	lvl1 = loadTilemap("tilemap.png", "back.png", tileSheet);

	SpriteSheet playerSprite = loadSpriteSheet("sprites.png", (Vec2D){64,64},
												(Vec2D){384, 128});
	Entity player = initEntity((Vec2D){0, 200}, playerSprite);

	loadWorld(WIDTH, HEIGHT, &player);

	prepOGL();
	while(!shouldCloseWindow()) {
		startLoop();
		prepRender();
		renderWorld(&lvl1);

		pMovement(&player, lvl1.map);
		for(int i = 0; i < lvl1.nEnemies; ++i) {
			activateEnemy(&lvl1.enemies[i], lvl1.map, getDelta());
		}

		endLoop();
	}

	freelvl(lvl1);
	worldCleanUp();
	displayCleanUp();
}