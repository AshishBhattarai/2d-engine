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
inline mat4_t createMat4(mat4_t dest){

	mat4_t mat4 = (mat4_t)malloc(sizeof(float)*16);
	//if ma is not a nullptr copy mat
	if(dest) {

		mat4[0] = dest[0];	mat4[4] = dest[4];	mat4[8] = dest[8];
		mat4[1] = dest[1];	mat4[5] = dest[5];	mat4[9] = dest[9];
		mat4[2] = dest[2];	mat4[6] = dest[6];	mat4[10] = dest[10];
		mat4[3] = dest[3];	mat4[7] = dest[7];	mat4[11] = dest[11];

		mat4[12] = dest[12];
		mat4[13] = dest[13];
		mat4[14] = dest[14];
		mat4[15] = dest[15];
	}
	return mat4;
}

//load identity matrix to the given map4
inline void loadIdentity(mat4_t mat4) {

	mat4[0] = 1.0;	mat4[4] = 0.0;	mat4[8] = 0.0;	mat4[12] = 0.0;
	mat4[1] = 0.0;	mat4[5] = 1.0;	mat4[9] = 0.0;	mat4[13] = 0.0;
	mat4[2] = 0.0;	mat4[6] = 0.0;	mat4[10] = 1.0;	mat4[14] = 0.0;
	mat4[3] = 0.0;	mat4[7] = 0.0;	mat4[11] = 0.0;	mat4[15] = 1.0;

}
/*
* Translates the given matrix by the given vec3
* and frees the given matrix
*/
inline mat4_t translate(mat4_t mat4, vec3_t vec) {

	float x = vec[0], y = vec[1], z = vec[2];

	if(!mat4)
		loadIdentity(mat4);

	mat4_t dest = createMat4(NULL);

	dest[0] = mat4[0];	dest[4] = mat4[4];	dest[8] = mat4[8];
	dest[1] = mat4[1];	dest[5] = mat4[5];	dest[9] = mat4[9];
	dest[2] = mat4[2]; 	dest[6] = mat4[6];	dest[10] = mat4[10];
	dest[3] = mat4[3]; 	dest[7] = mat4[7];	dest[11] = mat4[11];

	dest[12] = mat4[0] * x + mat4[4] * y + mat4[8] * z + mat4[12];
	dest[13] = mat4[1] * x + mat4[5] * y + mat4[9] * z + mat4[13];
	dest[14] = mat4[2] * x + mat4[6] * y + mat4[10] * z + mat4[14];
	dest[15] = mat4[3] * x + mat4[7] * y + mat4[11] * z + mat4[15];

	free(mat4);

	return dest;
}

/*
* scales the given matrix by the given vec3
* and frees the given matix(parameter)
*/
inline mat4_t scale(mat4_t mat4, vec3_t vec) {

	float x = vec[0], y = vec[1], z = vec[2];

	if(!mat4)
		loadIdentity(mat4);

	mat4_t dest = createMat4(NULL);

	dest[0] = mat4[0] * x;	dest[4] = mat4[4] * y;	dest[8] = mat4[8] * z;
	dest[1] = mat4[1] * x;	dest[5] = mat4[5] * y;	dest[9] = mat4[9] * z;
	dest[2] = mat4[2] * x; 	dest[6] = mat4[6] * y;	dest[10] = mat4[10] * z;
	dest[3] = mat4[3] * x;	dest[7] = mat4[7] * y;	dest[11] = mat4[11] * z;

	dest[12] = mat4[12];
	dest[13] = mat4[13];
	dest[14] = mat4[14];
	dest[15] = mat4[15];

	free(mat4);

	return dest;
}

#endif