#version 400 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 textCoords;
layout(location = 2) in vec2 textCoords2;


out vec2 pass_textCoords;

uniform mat4 projectionMatrix;
uniform mat4 compositeMatrix;
uniform mat4 viewMatrix;
uniform bool facing;

void main(void) {

	gl_Position = projectionMatrix * viewMatrix * compositeMatrix * vec4(vertexPos,1.0);

	if(facing)
		pass_textCoords = textCoords;
	else
		pass_textCoords = textCoords2;
}