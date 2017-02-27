#ifndef WORLD_H
#define WORLD_H


#include "Level.h"
#include "Entity.h"

//Loads Word with give width & height
void loadWorld(float w, float h, Entity *player);

//Prepare OGL
void prepOGL();
//prepare to render something one the screen
void prepRender();
//Reneder the world
void renderWorld();
//Cleaup up shaders..
void worldCleanUp();


#endif