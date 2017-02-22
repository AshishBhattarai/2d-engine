#ifndef ENTITY_H
#define ENTITY_H

#include "GMath.h"
#include "Texture.h"
#include "Tilemap.h"
#include <stdbool.h>

#define SPEED 0.2f
#define COLL_SIZE 60.0f
#define OFF_SET 32.0f //Collision offset for entity X-axis
#define GRAVITY 0.001f
#define JUMP .5f //.6f

typedef struct Entity Entity;

struct Entity {
	Vec2D pos;
	GLuint texture;
	bool jumpCd;
	bool canjump;
};

//take movementValue applies gravity + collision & sets entities new position
void moveEntity(Vec2D *movVal, Entity *entity, Tilemap map, float delta);

#endif