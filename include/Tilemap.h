#ifndef TILEMAP_H
#define TILEMAP_H

#include "GMath.h"
#include "GL/glew.h"
#include <stdbool.h>

#define TILE_SIZE 64

typedef struct {
	Vec2D pos;
	GLuint texture;
	bool rigid;
} Tile;

typedef struct {
	Tile* tiles;
	int nTiles;
} Tilemap;

//uses bitmap to load tiles coordinates to any array of Tile
Tilemap loadTiles(const char* bitMapFile);

//free the loaded tiles
void freeMap(Tilemap* map);

#endif