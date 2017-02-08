#ifndef WORLD_H
#define WORLD_H

//Loads Word with give width & height
void loadWorld(float w, float h);

//Prepare OGL
void prepOGL();
//prepare to render something one the screen
void prepRender();
//Reneder the world
void renderWorld();
//Cleaup up shaders..
void worldCleanUp();


#endif