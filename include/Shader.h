#ifndef SHADER_H
#define SHADER_H

#include "GMath.h"
#include <GL/glew.h>
#include <stdbool.h>

//Loades vertex, fragment shader
//GLuint shaders(const char* vertexFile, const char* fragmentFile);
GLuint createWShader(const char* vertexFile, const char* fragmentFile);

//Use the loaded shader
void bindShader(GLuint program);

void unBindShader();

//delete the shader program
void shaderCleanUp(GLuint program);

//load Composite matrix to shader
void loadCompositeMatrix(float* mat4);

void loadProjectionMatrix(float* proj);

void loadViewMatrix(float* view);

void loadFrame(Vec2D frame);

void loadSpriteSize(Vec2D size);

void setFacing(bool bol);

#endif