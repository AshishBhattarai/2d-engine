#ifndef TILE_H
#define TILE_H

#include "GMath.h"
#include "GL/glew.h"

typedef struct Tile Tile;

struct Tile {
	Vec2D pos;
	GLuint texture;
};

#endif