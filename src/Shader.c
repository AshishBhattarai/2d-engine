#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

GLuint program;


GLuint loadShader(const char *file, GLuint type) {

	FILE *fp = NULL;
	int size = 0;

	fp = fopen(file, "r");
	if(!fp)
		fprintf(stderr, "Error. Failed to open the file: %s\n", file);

	//Get the size of file(no. of chars in file)
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	const char *source = (char*)malloc((size+1)*sizeof(float));

	//read the file into the source
	fread((char*)source, size, 1, fp);

 	fclose(fp);

	//Create - Link Source - Compile Shader
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	free((char*)source); //free source data

	//Check for errors
	GLint compileStatus = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if(!compileStatus) {
		fprintf(stderr, "Error compilation failed. %s\n", file);
		GLint maxLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		//errorLog to store error messages
		char *errorLog  = (char *)malloc((maxLength+1)*sizeof(char));
		glGetShaderInfoLog(shader, maxLength, NULL, errorLog);
		fprintf(stderr, "%s\n" ,errorLog);
		free(errorLog); //free error data
		glDeleteShader(shader); //delete failed shader
	}

	return shader;
}

void shaders(const char* vertexFile, const char* fragmentFile) {
	//loadShaders
	GLuint vertex = loadShader(vertexFile, GL_VERTEX_SHADER);
	GLuint fragment = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	//create programs
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	//Bind attributes
	glBindAttribLocation(program, 0, "vertexPos");
	glBindAttribLocation(program, 1, "textCoords");

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void useShader() {
	glUseProgram(program);
}

void shaderCleanUp() {
	glUseProgram(0);
	glDeleteProgram(program);
	fprintf(stderr, "Shader Deleted.\n");
}