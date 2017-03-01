#ifndef LEVEL_H
#define LEVEL_H

#include "Tilemap.h"
#include "Enemy.h"
#include "GL/gl.h"

typedef struct {
	Tilemap map;
	Enemy *enemies;
	int nEnemies;
	GLuint bg;
} Level;

Level loadTilemap(const char* bitMap, const char* spriteSheet, const char* bg,
			      const char* aSpriteSheet);


//free the loaded map
void freelvl(Level lvl);

#endif