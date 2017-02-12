#ifndef TILEMAP_H
#define TILEMAP_H

#include "GMath.h"
#include "GL/glew.h"

typedef struct Tile Tile;

struct Tile {
	Vec2D pos;
	GLuint texture;
};

typedef struct Tilemap Tilemap;

struct Tilemap {
	Tile* tiles;
	int nTiles;
};

//uses bitmap to load tiles coordinates to any array of Tile
Tilemap loadTiles(const char* bitMapFile);

//free the loaded tiles
void freeMap(Tilemap* map);

#endif