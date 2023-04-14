#version 430 core

in vec3 vertexColor;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

void main() {
  //float originalZ = gl_FragCoord.z / gl_FragCoord.w;
  FragColor = vec4(vertexColor, 1.0);
  // check whether fragment output is higher than threshold, if so output as brightness color
  float brightness = dot(FragColor.rgb, vec3(1.0));
  if(brightness > 0.5)
      BrightColor = vec4(FragColor.rgb, 1.0);
  else
      BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}