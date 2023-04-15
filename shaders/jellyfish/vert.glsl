#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

layout(location = 0) uniform mat4 MVP;
layout(location = 1) uniform float t;

out vec3 vertexColor;

float sinRange(float x, float ymin, float ymax) {
  
  return 0.5 * (ymin + ymax) + 0.5 * (ymax - ymin) * sin(x);
}

float cosRange(float x, float ymin, float ymax) {
  return 0.5 * (ymin + ymax) + 0.5 * (ymax - ymin) * cos(x);

}

void main() {
  vertexColor = color;
  gl_Position = MVP * vec4(
    pos.x * cosRange(3 * t + 3 * pos.z, 0.7, 1.0), 
    pos.y * sinRange(3 * t + 3 * pos.z, 0.7, 1.0),
    pos.z,
    1.0
  );
}