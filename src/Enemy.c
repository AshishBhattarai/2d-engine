#include "Enemy.h"


Vec2D em; //enemy movement
Vec2D oldPos;

void moveEnemy(Vec2D *val, Enemy *enemy, Tilemap map, float delta) {

	//Gravity
	val->y -= GRAVITY*delta;

	//X Position
	oldPos = enemy->entity.pos;
	enemy->entity.pos.x += val->x*delta;
	if(tileCollision(enemy->entity, map)) { //check for collision
		//if collision
		enemy->entity.pos = oldPos;
		if(enemy->reach)
			enemy->reach = false;
		else
			enemy->reach = true;
	}

	//Y Position
	oldPos = enemy->entity.pos;
	enemy->entity.pos.y += val->y*delta;
	if(tileCollision(enemy->entity, map)) {
		enemy->entity.pos = oldPos;
	}

	//Screen border collision
	if(enemy->entity.pos.x <= 0)
		enemy->entity.pos.x = 0;
}

void patrol(Enemy *enemy) {
	if(!enemy->reach) {
		em.x += 0.1f;
		if(enemy->entity.pos.x >= enemy->point.x) {
			enemy->entity.pos.x = enemy->point.x;
			enemy->reach = true;
		}
		enemy->entity.facing = true;
	}
	if(enemy->reach) {
		em.x -= 0.1f;
		if(enemy->entity.pos.x <= enemy->point.y) {
			enemy->entity.pos.x = enemy->point.y;
			enemy->reach = false;
		}
		enemy->entity.facing = false;
	}
}

void activateEnemy(Enemy *enemy, Tilemap tilemap, float delta) {
	em.x = 0;
	em.y = 0;
	if(enemy->type == NORMAL)
		patrol(enemy);

	moveEnemy(&em, enemy, tilemap, delta);
}