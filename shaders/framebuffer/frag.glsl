#version 430 core

in vec2 texCoords;
out vec4 FragColor;

layout(location = 0) uniform sampler2D screenTex;

void main() {
	FragColor = texture(screenTex, texCoords);
}