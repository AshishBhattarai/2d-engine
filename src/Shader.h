#ifndef SHADER_H
#define SHADER_H

//Loades vertex, fragment shader
void shaders(const char* vertexFile, const char* fragmentFile);

//Use the loaded shader
void useShader();

//delete the shader program
void shaderCleanUp();


#endif