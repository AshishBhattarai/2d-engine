#ifndef SHADER_H
#define SHADER_H

#include "GMath.h"

//Loades vertex, fragment shader
void shaders(const char* vertexFile, const char* fragmentFile);

//Use the loaded shader
void bindShader();

void unBindShader();

//delete the shader program
void shaderCleanUp();

//load Composite matrix to shader
void loadCompositeMatrix(float* mat4);

void loadProjectionMatrix(float* proj);


#endif