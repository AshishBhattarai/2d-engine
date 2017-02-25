#include "SpriteSheet.h"
#include <SOIL/SOIL.h>
#include <stdio.h>

//Load texture from the given file
GLuint loadTexture(const char* file) {
	int width, height;
	GLuint texture;

	//Load image
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGBA);
	if(!image)
		fprintf(stderr, "Failed to load the texture. %s\n",  SOIL_last_result());

	//Generate textures
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	return texture;
}

SpriteSheet loadSpriteSheet(char* file, Vec2D spriteD, Vec2D sheetD) {
	SpriteSheet spriteSheet;
	spriteSheet.texture = loadTexture(file);
	spriteSheet.sheetD = sheetD;
	spriteSheet.spriteD = spriteD;
	spriteSheet.nRowCol.x = sheetD.x / spriteD.x;
	spriteSheet.nRowCol.y = sheetD.y / spriteD.y;
	spriteSheet.spriteSize.x = spriteD.x / sheetD.x;
	spriteSheet.spriteSize.y = spriteD.y / sheetD.y;

	return spriteSheet;
}

static Vec2D sprite;

//Get sprite on x,y postion on da given spriteSheet
Vec2D getSprite(SpriteSheet spriteSheet, int x, int y) {

	if (x <= spriteSheet.nRowCol.x)
		sprite.x = (spriteSheet.spriteSize.x)*x;
	else
		sprite.x = 0;
	if (y <= spriteSheet.nRowCol.y)
		sprite.y = (spriteSheet.spriteSize.y)*y;
	else
		sprite.y = 0;

	return sprite;
}
