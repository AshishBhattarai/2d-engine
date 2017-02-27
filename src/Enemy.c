#include "Enemy.h"


Vec2D em; //enemy movement
bool reach = false;


static void patrol(Enemy *enemy) {
	if(!reach) {
		em.x += 0.1f;
		reach = (enemy->entity.pos.x >= enemy->point.x) ? true : false;
		enemy->entity.facing = true;
	} else if(reach) {
		em.x -= 0.1f;
		reach = (enemy->entity.pos.x <= enemy->point.y) ? false : true;
		enemy->entity.facing = false;
	}
}

void activateEnemy(Enemy *enemy, Tilemap tilemap, float delta) {
	if(enemy->type == NORMAL)
		patrol(enemy);

	moveEntity(&em, &enemy->entity, tilemap, delta);
}