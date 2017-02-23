#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>


static GLuint program;

//location of projection matrix &composite matrix in shaders
static GLint locProjection, locComposite, locView, facing;

static GLuint loadShader(const char *file, GLuint type) {

	FILE *fp = NULL;
	int size = 0;

	fp = fopen(file, "r");
	if(!fp)
		fprintf(stderr, "Error. Failed to open the file: %s\n", file);

	//Get the size of file(no. of chars in file)
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	char *source = (char*)malloc(size*sizeof(char)+1);

	//read the file into the source
	fread((char*)source, size, 1, fp);

 	fclose(fp);
	source[size] = '\0';

	//Create - Link Source - Compile Shader
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar *const*)&source, NULL);
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

static void getAllUniformLocs() {
	locProjection = glGetUniformLocation(program, "projectionMatrix");
	locComposite = glGetUniformLocation(program, "compositeMatrix");
	locView = glGetUniformLocation(program, "viewMatrix");
	facing = glGetUniformLocation(program, "facing");
}

static void loadMatrix(GLuint location, float* mat4) {
	glUniformMatrix4fv(location, 1, GL_FALSE, mat4);
}

static void loadBool(GLuint location, bool bol) {
	glUniform1i(location, bol);
}

void loadProjectionMatrix(float* proj) {
	loadMatrix(locProjection, proj);
}

void loadCompositeMatrix(float* mat4) {
	loadMatrix(locComposite, mat4);
}

void loadViewMatrix(float* view) {
	loadMatrix(locView, view);
}

void setFacing(bool bol) {
	loadBool(facing, bol);
}

void shaders(const char* vertexFile, const char* fragmentFile) {
	//loadShaders
	GLuint fragment = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	GLuint vertex = loadShader(vertexFile, GL_VERTEX_SHADER);

	//create programs
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	//Bind attributes
	glBindAttribLocation(program, 0, "vertexPos");
	glBindAttribLocation(program, 1, "textCoords");
	glBindAttribLocation(program, 2, "textCoords2");

	glLinkProgram(program);
	glValidateProgram(program);
	getAllUniformLocs();

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void bindShader() {
	glUseProgram(program);
}

void unBindShader() {
	glUseProgram(0);
}

void shaderCleanUp() {
	glUseProgram(0);
	glDeleteProgram(program);
	fprintf(stderr, "Shader Deleted.\n");
}