#ifndef ANIMATION_H
#define ANIMATION_H

#define AFPS 0.1f

#define IDEL 1
#define WALKING 0
#define JUMPING 2

#include "SpriteSheet.h"

typedef struct {
	SpriteSheet spriteSheet;
	float lastFrame;
	int state;
	Vec2D frame;
	int frameCnt;
} Animation;

//Initialize Animation
Animation initAnimation(SpriteSheet spriteSheet);

void animate(Animation *animation, int mode);

#endif