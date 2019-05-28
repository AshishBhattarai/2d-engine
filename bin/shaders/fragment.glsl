#version 400 core

in vec2 pass_textCoords;

out vec4 color;

uniform sampler2D textureSampler;

void main(void) {
	color = texture(textureSampler, pass_textCoords);
}
