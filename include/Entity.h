#ifndef ENTITY_H
#define ENTITY_H

#include "Animation.h"
#include "Tilemap.h"
#include <stdbool.h>

#define SPEED 0.2f
#define COLL_SIZE 60.0f
#define OFF_SET 16.0f //Collision offset for entity X-axis
#define GRAVITY 0.001f
#define JUMP .5f //.6f


typedef struct  {
	Vec2D pos;
	Animation animation;
	bool facing;
	bool jumpCd;
	bool canjump;
} Entity;

//Initialize Entity
Entity initEntity(Vec2D pos, SpriteSheet spriteSheet);

bool tileCollision(Entity entity, Tilemap map);

//take movementValue applies gravity + collision & sets entities new position
void moveEntity(Vec2D *movVal, Entity *entity, Tilemap map, float delta);

#endif