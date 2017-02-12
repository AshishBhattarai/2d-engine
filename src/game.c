#include "Display.h"
#include "Texture.h"
#include "World.h"
#include "Tilemap.h"
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

int main() {

	createDisplay(WIDTH, HEIGHT, "2D-Engine");
	
	//Image - 90 C-CW - Flip Horizontally - Flip V
	Tilemap map = loadTiles("t1.png");

	loadWorld(WIDTH, HEIGHT, map);

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