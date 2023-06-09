#version 430 core

layout(location = 0) in vec2 pos;

out vec2 texCoords;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);
	texCoords = 0.5 * pos + 0.5;
}