#include "Entity.h"
#include <stdio.h>

Vec2D oldPos;

static inline int compareVec2D(Vec2D vec1, Vec2D vec2) {
	if((vec1.x+COLL_SIZE-OFF_SET >= vec2.x) && (vec1.y+COLL_SIZE >= vec2.y) &&
		((vec1.x-COLL_SIZE+OFF_SET <= vec2.x) && (vec1.y-COLL_SIZE<= vec2.y))) {
		return 1;
	} else
		return 0;
}

Entity initEntity(Vec2D pos, SpriteSheet spriteSheet) {

	Entity entity;
	entity.pos = pos;
	entity.animation = initAnimation(spriteSheet);
	entity.facing = true;
	entity.jumpCd = false;
	entity.canjump = false;

	return entity;
}

bool tileCollision(Entity entity, Tilemap map) {

	Vec2D tilePos;
	bool xOverlaps = false, yOverlaps = false, collision = false;
	for(int i = 0; i < map.nTiles; ++i ) {
		//Check collision only for rigid tiles
		if(map.tiles[i].rigid) {
			//map.tiles[i].pos.x*TILE_SIZE - Gives tile postion in da world
			tilePos.x = map.tiles[i].pos.x*TILE_SIZE;
			tilePos.y = map.tiles[i].pos.y*TILE_SIZE;

			if(compareVec2D(entity.pos, tilePos)) {
				xOverlaps = entity.pos.x <= tilePos.x+COLL_SIZE &&
							entity.pos.x+COLL_SIZE >= tilePos.x;
				yOverlaps = entity.pos.y <= tilePos.y+COLL_SIZE &&
							entity.pos.y+COLL_SIZE >= tilePos.y;

			collision = xOverlaps && yOverlaps;
			}
		}
	}

	return collision;
}

void moveEntity(Vec2D *val, Entity *entity, Tilemap map, float delta) {

	//Gravity
	val->y -= GRAVITY*delta;

	//X Position
	oldPos = entity->pos;
	entity->pos.x += val->x*delta;
	if(tileCollision(*entity, map)) { //check for collision
		//if collision
		entity->pos = oldPos;
		val->x = 0;
	}

	//Y Position
	oldPos = entity->pos;
	entity->pos.y += val->y*delta;
	if(tileCollision(*entity, map)) {
		entity->pos = oldPos;
		//skip jump for 1 frame(solves sticking bug)
		if(entity->jumpCd) {
			entity->canjump = true;
			entity->jumpCd = false;
		} else
			entity->jumpCd = true;
		val->y = 0;
	}

	//Screen border collision
	if(entity->pos.x <= 0)
		entity->pos.x = 0;
	else if(entity->pos.y <= 0)
		entity->pos.y = 0;

	val->x = 0;
}