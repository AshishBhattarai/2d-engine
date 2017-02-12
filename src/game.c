#include "Display.h"
#include "Texture.h"
#include "World.h"
#include "Tilemap.h"
#include "Level.h"
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

int main() {

	createDisplay(WIDTH, HEIGHT, "2D-Engine");


	Level lvl1;
	lvl1.map = loadTiles("t1.png"); //t1 - 90 C-CW - Flip Horizontally - Flip V
	lvl1.bg = loadTexture("back.png");

	loadWorld(WIDTH, HEIGHT, lvl1);

	prepOGL();
	while(!shouldCloseWindow()) {
		startLoop();
		prepRender();
		renderWorld();
		endLoop();
	}

	worldCleanUp();
	displayCleanUp();
}