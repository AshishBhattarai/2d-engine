#ifndef LEVEL_H
#define LEVEL_H

#include "Tilemap.h"
#include "GL/gl.h"

typedef struct {
	Tilemap map;
	GLuint bg;
} Level;

#endif