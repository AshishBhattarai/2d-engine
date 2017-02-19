#ifndef ENTITY_H
#define ENTITY_H

#include "GMath.h"
#include "Texture.h"
#include "Tilemap.h"
#include <stdbool.h>

#define SPEED 0.2f
#define COLL_SIZE 128

typedef struct Entity Entity;

struct Entity {
	Vec2D pos;
	GLuint texture;
};

void moveEntity(Entity *entity, float valX, float valY);

bool tileCollision(Entity entity, Tilemap map);

#endif