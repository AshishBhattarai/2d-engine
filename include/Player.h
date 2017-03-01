#ifndef PLAYER_H
#define PLAYER_H

#include "GMath.h"
#include "Entity.h"

typedef struct {
	Entity entity;

} Player;

Player initPlayer(Vec2D pos, const char *spriteSheet, Vec2D sheetSize);

void movePlayer(Entity *player, Tilemap map);

#endif