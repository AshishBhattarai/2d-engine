#ifndef ENTITY_H
#define ENTITY_H

#include "GMath.h"
#include "Texture.h"
#include "Tilemap.h"
#include <stdbool.h>

#define SPEED 0.2f
#define COLL_SIZE 60.0f
#define OFF_SET 16.0f //Collision offset for entity X-axis
#define GRAVITY 0.001f
#define JUMP .5f //.6f


typedef struct  {
	Vec2D pos;
	GLuint texture;
	bool facing;
	bool jumpCd;
	bool canjump;
} Entity;


static const Entity entityDef = {
	.pos.x = 0,
	.pos.y = 0,
	.texture = 0,
	.facing = true,
	.jumpCd = false,
	.canjump = false
};

//take movementValue applies gravity + collision & sets entities new position
void moveEntity(Vec2D *movVal, Entity *entity, Tilemap map, float delta);

#endif