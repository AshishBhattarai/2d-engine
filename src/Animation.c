#include "Animation.h"
#include "GLFW/glfw3.h"

Animation initAnimation(SpriteSheet spriteSheet) {

	Animation animation;
	animation.spriteSheet = spriteSheet;
	animation.state = IDEL;
	animation.lastFrame = glfwGetTime();
	animation.frame.x = 0.0f;
	animation.frame.y = 0.0f;
	animation.frameCnt = 1;

	return animation;
}

void animate(Animation *animation) {

	if((glfwGetTime() - animation->lastFrame) > AFPS) {

		animation->frame = getSprite(animation->spriteSheet, animation->frameCnt,
									 animation->state);

		if(animation->frameCnt > animation->spriteSheet.nRowCol.x) {
			animation->frameCnt = 1;
		} else {
			++animation->frameCnt;
		}
		animation->lastFrame = glfwGetTime();
	}
}