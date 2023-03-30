#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in mat4 Model;
//layout(location = 3) in vec3 color;

layout(location = 0) uniform mat4 VP;

out vec3 vertexColor;

void main() {
  vec3 color = vec3(Model[0][3], Model[1][3], Model[2][3]);
  vec3 rotated_normal = normalize(mat3(Model) * normal);
  vertexColor = max(dot(rotated_normal.xyz, vec3(0.0, 1.0, 0.0)), 0.1) * color;

  vec4 world_pos = vec4(mat3(Model) * pos + Model[3].xyz, 1.0);
  gl_Position = VP * world_pos;
}