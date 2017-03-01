#include "Display.h"
#include "World.h"
#include "Player.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

int main() {

	createDisplay(WIDTH, HEIGHT, "2D-Engine");

	Player player = initPlayer((Vec2D){0, 200}, "knight.png", (Vec2D){256, 128});

	//t1 - 90 C-CW - Flip Horizontally - Flip V
	Level lvl1;
	lvl1 = loadTilemap("tilemap.png", "tilesheet.png", "back.png", "coin.png");

	loadWorld(WIDTH, HEIGHT, &player.entity);

	prepOGL();
	while(!shouldCloseWindow()) {
		startLoop();
		prepRender();
		renderWorld(&lvl1);

		movePlayer(&player.entity, lvl1.map);
		for(int i = 0; i < lvl1.nEnemies; ++i) {
			activateEnemy(&lvl1.enemies[i], lvl1.map, getDelta());
		}

		endLoop();
	}

	freelvl(lvl1);
	worldCleanUp();
	displayCleanUp();
}