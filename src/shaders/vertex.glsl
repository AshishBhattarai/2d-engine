#version 400 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 textCoords;

out vec2 pass_textCoords;

void main(void) {

	gl_Position = vec4(vertexPos,1.0);
	pass_textCoords = textCoords;
}