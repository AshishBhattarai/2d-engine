#include <Texture.h>
#include <SOIL/SOIL.h>
#include <stdio.h>

//Load texture from the given file
GLuint loadTexture(const char* file) {
	int width, height;
	GLuint texture;

	//Load image
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGBA);
	if(!image)
		fprintf(stderr, "Failed to load the texture. %s\n",  SOIL_last_result());

	//Generate textures
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	return texture;
}
