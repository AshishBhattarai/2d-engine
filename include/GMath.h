#ifndef GMATH_H
#define GMATH_H

#include <stdlib.h>

typedef float* mat4_t;
typedef float* vec3_t;
typedef float* vec2_t;

/*
 * Math library to handel Opengl matrices & vertices
 *
 * Uses single array column major matrix
 * Supports 3D & 2D Vectors
*/

//Vector


//Matrix


//if mat is a nullptr allocates memory ofr 16 elem vector only
//if mat is not null copys mat too
static inline mat4_t createMat4(mat4_t destMat4){

	mat4_t mat4 = (mat4_t)malloc(sizeof(float)*16);
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
static inline void loadIdentity(mat4_t mat4) {

	mat4[0] = 1.0;	mat4[4] = 0.0;	mat4[8] = 0.0;	mat4[12] = 0.0;
	mat4[1] = 0.0;	mat4[5] = 1.0;	mat4[9] = 0.0;	mat4[13] = 0.0;
	mat4[2] = 0.0;	mat4[6] = 0.0;	mat4[10] = 1.0;	mat4[14] = 0.0;
	mat4[3] = 0.0;	mat4[7] = 0.0;	mat4[11] = 0.0;	mat4[15] = 1.0;

}
/*
* Translates the given matrix by the given vec3
* and frees the given matrix
*/
static inline void translate(mat4_t mat4, vec3_t vec) {

	float x = vec[0], y = vec[1], z = vec[2];

	if(!mat4)
		loadIdentity(mat4);

	float destMat4[16];

	destMat4[0] = mat4[0];	destMat4[4] = mat4[4];	destMat4[8] = mat4[8];
	destMat4[1] = mat4[1];	destMat4[5] = mat4[5];	destMat4[9] = mat4[9];
	destMat4[2] = mat4[2]; 	destMat4[6] = mat4[6];	destMat4[10] = mat4[10];
	destMat4[3] = mat4[3]; 	destMat4[7] = mat4[7];	destMat4[11] = mat4[11];

	destMat4[12] = mat4[0] * x + mat4[4] * y + mat4[8] * z + mat4[12];
	destMat4[13] = mat4[1] * x + mat4[5] * y + mat4[9] * z + mat4[13];
	destMat4[14] = mat4[2] * x + mat4[6] * y + mat4[10] * z + mat4[14];
	destMat4[15] = mat4[3] * x + mat4[7] * y + mat4[11] * z + mat4[15];

	for(int i = 0; i < 16; ++i) {
		mat4[i] = destMat4[i];
	}
}

/*
* scales the given matrix by the given vec3
* and frees the given matix(parameter)
*/
static inline void scale(mat4_t mat4, float val) {

	float x = val, y = val, z= val;

	if(!mat4)
		loadIdentity(mat4);

	float destMat4[16];

	destMat4[0] = mat4[0] * x;	destMat4[4] = mat4[4] * y;	destMat4[8] = mat4[8] * z;
	destMat4[1] = mat4[1] * x;	destMat4[5] = mat4[5] * y;	destMat4[9] = mat4[9] * z;
	destMat4[2] = mat4[2] * x; 	destMat4[6] = mat4[6] * y;	destMat4[10] = mat4[10] * z;
	destMat4[3] = mat4[3] * x;	destMat4[7] = mat4[7] * y;	destMat4[11] = mat4[11] * z;

	destMat4[12] = mat4[12];
	destMat4[13] = mat4[13];
	destMat4[14] = mat4[14];
	destMat4[15] = mat4[15];

	for(int i = 0; i < 16; ++i) {
		mat4[i] = destMat4[i];
	}
}


// Orthogonal projection matrix
static inline mat4_t loadOrtho(float left, float right, float bottom, float top,
						float near, float far) {

	mat4_t destMat4 = createMat4(NULL);
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