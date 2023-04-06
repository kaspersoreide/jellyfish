#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

layout(location = 0) uniform mat4 MVP;

out vec3 vertexColor;

void main() {
  vertexColor = color;
  gl_Position = MVP * vec4(pos, 1.0);
}