#include "Entity.h"
#include <stdio.h>

void moveEntity(Entity *entity, float valX, float valY) {
	entity->pos.x += valX;
	entity->pos.y += valY;
}

static inline int compareVec2D(Vec2D vec1, Vec2D vec2) {
	if(vec1.x >= vec2.x && vec1.y >= vec2.y && vec1.x <= vec2.x+COLL_SIZE &&
	   vec1.y<= vec2.y+COLL_SIZE) {
		return 1;
	} else
		return 0;
}

bool tileCollision(Entity entity, Tilemap map) {
	bool xOverlaps, yOverlaps, collision;
	Vec2D tilePos;
	for(int i = 0; i < map.nTiles; ++i ) {
		//map.tiles[i].pos.x*TILE_SIZE - Gives tile postion in da world
		tilePos.x = map.tiles[i].pos.x*TILE_SIZE-TILE_SIZE;
		tilePos.y = map.tiles[i].pos.y*TILE_SIZE-TILE_SIZE;
		if(compareVec2D(entity.pos, tilePos)) {
			printf("Checking\n");
			xOverlaps = entity.pos.x <= tilePos.x+COLL_SIZE &&
						entity.pos.x+TILE_SIZE >= tilePos.x;
			yOverlaps = entity.pos.y <= tilePos.y+COLL_SIZE &&
						entity.pos.y+TILE_SIZE >= tilePos.y;
		} else {
			return 0;
		}
		collision = xOverlaps && yOverlaps;
	}

	return collision;
}
