#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "GMath.h"
#include <GL/glew.h>

typedef struct {
	GLuint texture;
	Vec2D sheetD;
	Vec2D spriteD;
	Vec2D spriteSize;
	Vec2D nRowCol;

} SpriteSheet;

//Load texture from the given file
GLuint loadTexture(const char* file);

SpriteSheet loadSpriteSheet(char* file, Vec2D spriteD, Vec2D sheetD);

//Get sprite on x,y postion on da given spriteSheet
Vec2D getSprite(SpriteSheet spriteSheet, int x, int y);

#endif