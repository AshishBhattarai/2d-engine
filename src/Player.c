#include "Player.h"
#include "SpriteSheet.h"
#include "Display.h"
#include <GLFW/glfw3.h>


Vec2D movement;

static int oldState = GLFW_RELEASE;

Player initPlayer(Vec2D pos, const char *spriteSheet, Vec2D sheetSize) {

	Player player;
	SpriteSheet playerSprite = loadSpriteSheet(spriteSheet, (Vec2D){64,64},
												sheetSize);
	player.entity = initEntity(pos, playerSprite);

	return player;
}

void movePlayer(Entity *player, Tilemap map) {

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

