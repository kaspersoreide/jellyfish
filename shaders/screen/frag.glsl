#version 430 core

in vec2 texCoords;
out vec4 FragColor;

layout(location = 0) uniform sampler2D screenTex;
layout(location = 1) uniform sampler2D bloomTex;

void main() {
	const float exposure = 2.5;
	const float gamma = 1.2;
	vec3 color1 = texture(screenTex, texCoords).rgb;
	vec3 color2 = texture(bloomTex, texCoords).rgb;
	vec3 color = color1 + color2;
	
	// map to range [0, 1]
	vec3 result = vec3(1.0) - exp(-color * exposure);
	// gamma correction
    result = pow(result, vec3(1.0 / gamma));

	FragColor = vec4(result, 1.0);
}