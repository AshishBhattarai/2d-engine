#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

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