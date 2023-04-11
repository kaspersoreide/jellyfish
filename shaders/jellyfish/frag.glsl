#version 430 core

in vec3 vertexColor;

out vec3 FragColor;

void main() {
  //float originalZ = gl_FragCoord.z / gl_FragCoord.w;
  FragColor = 5.0 * vertexColor;
}