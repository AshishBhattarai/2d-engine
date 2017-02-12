#ifndef LEVEL_H
#define LEVEL_H

#include "Texture.h"
#include "Tilemap.h"
#include "GL/gl.h"

typedef struct level Level;

struct level {
	Tilemap map;
	GLuint bg;
};

#endif