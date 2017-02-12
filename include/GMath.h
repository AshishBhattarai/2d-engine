#ifndef GMATH_H
#define GMATH_H

#include <stdlib.h>
#include <math.h>

/*
 * Math library to handel Opengl matrices & vertices
 *
 * Uses single array column major matrix
 * Supports 3D & 2D Vectors
*/

typedef struct vec2 Vec2D;

//Vector
struct vec2 {
	float x;
	float y;
};


static inline float magnitude2D(Vec2D vec) {
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

static inline Vec2D normalie2D(Vec2D vec) {
	float mag = magnitude2D(vec);
	return (Vec2D){vec.x/mag, vec.y/mag};
}

static inline float dotPorduct2D(Vec2D vec1, Vec2D vec2) {
	return (vec1.x*vec2.x) + (vec1.y*vec2.y);
}

static inline Vec2D vecMult(Vec2D vec1, float val) {
	return (Vec2D){vec1.x*val, vec1.y*val};
}

//Matrix


//if mat is a nullptr allocates memory ofr 16 elem vector only
//if mat is not null copys mat too
static inline float* createMat4(float* destMat4){

	float* mat4 = (float*)malloc(sizeof(float)*16);
	//if ma is not a nullptr copy mat
	if(destMat4) {

		mat4[0] = destMat4[0];	mat4[4] = destMat4[4];	mat4[8] = destMat4[8];
		mat4[1] = destMat4[1];	mat4[5] = destMat4[5];	mat4[9] = destMat4[9];
		mat4[2] = destMat4[2];	mat4[6] = destMat4[6];	mat4[10] = destMat4[10];
		mat4[3] = destMat4[3];	mat4[7] = destMat4[7];	mat4[11] = destMat4[11];

		mat4[12] = destMat4[12];
		mat4[13] = destMat4[13];
		mat4[14] = destMat4[14];
		mat4[15] = destMat4[15];
	}
	return mat4;
}

//load identity matrix to the given map4
static inline void loadIdentity(float* mat4) {

	mat4[0] = 1.0;	mat4[4] = 0.0;	mat4[8] = 0.0;	mat4[12] = 0.0;
	mat4[1] = 0.0;	mat4[5] = 1.0;	mat4[9] = 0.0;	mat4[13] = 0.0;
	mat4[2] = 0.0;	mat4[6] = 0.0;	mat4[10] = 1.0;	mat4[14] = 0.0;
	mat4[3] = 0.0;	mat4[7] = 0.0;	mat4[11] = 0.0;	mat4[15] = 1.0;

}
/*
* Translates the given matrix by the given vec3
* and frees the given matrix
*/
static inline void translateMat(float* mat4, Vec2D vec) {

	float z = 0; //no z-axis in 2D vector
	float destMat4[16];

	destMat4[0] = mat4[0];	destMat4[4] = mat4[4];	destMat4[8] = mat4[8];
	destMat4[1] = mat4[1];	destMat4[5] = mat4[5];	destMat4[9] = mat4[9];
	destMat4[2] = mat4[2]; 	destMat4[6] = mat4[6];	destMat4[10] = mat4[10];
	destMat4[3] = mat4[3]; 	destMat4[7] = mat4[7];	destMat4[11] = mat4[11];

	destMat4[12] = mat4[0] * vec.x + mat4[4] * vec.y + mat4[8] * z + mat4[12];
	destMat4[13] = mat4[1] * vec.x + mat4[5] * vec.y + mat4[9] * z + mat4[13];
	destMat4[14] = mat4[2] * vec.x + mat4[6] * vec.y + mat4[10] * z + mat4[14];
	destMat4[15] = mat4[3] * vec.x + mat4[7] * vec.y + mat4[11] * z + mat4[15];

	for(int i = 0; i < 16; ++i) {
		mat4[i] = destMat4[i];
	}
}

/*
* scales the given matrix by the given vec3
* and frees the given matix(parameter)
*/
static inline void scaleMat(float* mat4, float val) {

	float destMat4[16];

	destMat4[0] = mat4[0] * val;	destMat4[4] = mat4[4] * val;
	destMat4[1] = mat4[1] * val;	destMat4[5] = mat4[5] * val;
	destMat4[2] = mat4[2] * val; 	destMat4[6] = mat4[6] * val;
	destMat4[3] = mat4[3] * val;	destMat4[7] = mat4[7] * val;

	destMat4[8] = mat4[8] * val;
	destMat4[9] = mat4[9] * val;
	destMat4[10] = mat4[10] * val;
	destMat4[11] = mat4[11] * val;

	destMat4[12] = mat4[12];
	destMat4[13] = mat4[13];
	destMat4[14] = mat4[14];
	destMat4[15] = mat4[15];

	for(int i = 0; i < 16; ++i) {
		mat4[i] = destMat4[i];
	}
}

// Orthogonal projection matrix
static inline float* loadOrtho(float left, float right, float bottom, float top,
						float near, float far) {

	float* destMat4 = createMat4(NULL);
	loadIdentity(destMat4);

	destMat4[0] = 2 / (right - left);
	destMat4[5] = 2 / (top - bottom);
	destMat4[10] = -2 / (far - near);
	destMat4[12] = -(right + left) / (right - left);
	destMat4[13] = -(top + bottom) / (top - bottom);
	destMat4[14] = -(far + near) / (far - near);

	return destMat4;
}

#endif