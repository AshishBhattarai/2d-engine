#ifndef TILEMAP_H
#define TILEMAP_H

#include "GMath.h"
#include "GL/glew.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include <stdbool.h>

#define TILE_SIZE 64

typedef struct {
	Vec2D pos;
	Vec2D sprite;
	Animation animation;
	bool rigid;
	bool animate;
} Tile;

typedef struct {
	Tile* tiles;
	SpriteSheet spriteSheet;
	int nTiles;
} Tilemap;

#endif