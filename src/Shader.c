#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>

//wProgram - world shader program

//location of projection matrix &composite matrix in shaders
static GLint locWProjection, locWComposite, locWView, locWFrame, locWSpriteSize, WFacing;

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

static void loadMatrix(GLuint location, float* mat4) {
	glUniformMatrix4fv(location, 1, GL_FALSE, mat4);
}

static void loadBool(GLuint location, bool bol) {
	glUniform1i(location, bol);
}

static void loadVec2D(GLuint location, float x, float y) {
	glUniform2f(location, x, y);
}

//UniformLoaders
void loadProjectionMatrix(float* proj) {
	loadMatrix(locWProjection, proj);
}

void loadCompositeMatrix(float* mat4) {
	loadMatrix(locWComposite, mat4);
}

void loadViewMatrix(float* view) {
	loadMatrix(locWView, view);
}

void loadFrame(Vec2D frame) {
	loadVec2D(locWFrame, frame.x, frame.y);
}

void loadSpriteSize(Vec2D size) {
	loadVec2D(locWSpriteSize, size.x, size.y);
}

void setFacing(bool bol) {
	loadBool(WFacing, bol);
}

//for world shader
static void getAllUniformLocs(GLuint wProgram) {
	locWProjection = glGetUniformLocation(wProgram, "projectionMatrix");
	locWComposite = glGetUniformLocation(wProgram, "compositeMatrix");
	locWView = glGetUniformLocation(wProgram, "viewMatrix");
	locWFrame = glGetUniformLocation(wProgram, "frame");
	locWSpriteSize = glGetUniformLocation(wProgram, "spriteSize");
	WFacing = glGetUniformLocation(wProgram, "facing");
}

static void bindAttributes(GLuint wProgram) {
	//Bind attributes
	glBindAttribLocation(wProgram, 0, "vertexPos");
	glBindAttribLocation(wProgram, 1, "textCoords");
	glBindAttribLocation(wProgram, 2, "textCoords2");

}

GLuint shaders(const char* vertexFile, const char* fragmentFile, void (*bindAttrib)(GLuint)) {
	//loadShaders
	GLuint fragment = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	GLuint vertex = loadShader(vertexFile, GL_VERTEX_SHADER);

	//create programs
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	bindAttrib(program);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

//world shader
GLuint createWShader(const char* vertexFile, const char* fragmentFile) {

	GLuint wProgram = shaders(vertexFile, fragmentFile, bindAttributes);
	getAllUniformLocs(wProgram);
	return wProgram;
}

void bindShader(GLuint program) {
	glUseProgram(program);
}

void unBindShader() {
	glUseProgram(0);
}

void shaderCleanUp(GLuint wProgram) {
	glUseProgram(0);
	glDeleteProgram(wProgram);
	fprintf(stderr, "Shader Deleted.\n");
}