#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D screenTex;

void main() {
  FragColor = texture(screenTex, texCoords);
}