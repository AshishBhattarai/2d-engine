#ifndef ENTITY_H
#define ENTITY_H

#include "GMath.h"
#include "Texture.h"
#include "Tilemap.h"
#include <stdbool.h>

#define SPEED 0.2f
#define COLL_SIZE 128.0f
#define GRAVITY 0.005f

typedef struct Entity Entity;

struct Entity {
	Vec2D pos;
	GLuint texture;
};

//take movementValue applies gravity + collision & sets entities new position
void moveEntity(Vec2D *movVal, Entity *entity, Tilemap map, float delta);

#endif