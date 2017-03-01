#include "Enemy.h"


Vec2D em; //enemy movement
bool reach = false;


void patrol(Enemy *enemy) {
	if(!reach) {
		em.x += 0.1f;
		if(enemy->entity.pos.x >= enemy->point.x) {
			enemy->entity.pos.x = enemy->point.x;
			reach = true;
		}
		enemy->entity.facing = true;
	}
	if(reach) {
		em.x -= 0.1f;
		if(enemy->entity.pos.x <= enemy->point.y) {
			enemy->entity.pos.x = enemy->point.y;
			reach = false;
		}
		enemy->entity.facing = false;
	}
}



void activateEnemy(Enemy *enemy, Tilemap tilemap, float delta) {
	em.x = 0;
	em.y = 0;
	if(enemy->type == NORMAL)
		patrol(enemy);

	moveEntity(&em, &enemy->entity, tilemap, delta);
}