#include "Display.h"
#include <stdio.h>

int main() {

	createDisplay(640, 480, "2D-Engine");

	while(!shouldCloseWindow()) {
		startLoop();

		endLoop();
	}

	cleanUp();
}