#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

enum EnemyType {NORMAL, SPECIAL, BOSS};

typedef struct {

	Entity entity;
	Vec2D point;
	enum EnemyType type;
} Enemy;

void activateEnemy(Enemy *enemy, Tilemap tilemap, float delta);

#endif