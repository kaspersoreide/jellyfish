#version 430 core

in vec3 vertexColor;

out vec3 FragColor;

void main() {
  FragColor = vertexColor;
}