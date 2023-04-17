#version 430 core

in vec2 uv;
out vec4 FragColor;

uniform sampler2D image;
layout(location = 1) uniform bool isVertical;

/*
const int M = 4;
const int N = 2 * M + 1;
const float weights[N] = { 
    0.016216,
    0.054054, 
    0.1216216, 
    0.1945946, 
    0.227027, 
    0.1945946, 
    0.1216216, 
    0.054054, 
    0.016216 
};*/

const int M = 16;
const int N = 2 * M + 1;
// sigma = 10
const float weights[N] = {
	0.012318109844189502,
	0.014381474814203989,
	0.016623532195728208,
	0.019024086115486723,
	0.02155484948872149,
	0.02417948052890078,
	0.02685404941667096,
	0.0295279624870386,
	0.03214534135442581,
	0.03464682117793548,
	0.0369716985390341,
	0.039060328279673276,
	0.040856643282313365,
	0.04231065439216247,
	0.043380781642569775,
	0.044035873841196206,
	0.04425662519949865,
	0.044035873841196206,
	0.043380781642569775,
	0.04231065439216247,
	0.040856643282313365,
	0.039060328279673276,
	0.0369716985390341,
	0.03464682117793548,
	0.03214534135442581,
	0.0295279624870386,
	0.02685404941667096,
	0.02417948052890078,
	0.02155484948872149,
	0.019024086115486723,
	0.016623532195728208,
	0.014381474814203989,
	0.012318109844189502
};



void main() {
    vec2 pixelOffset = 1.0 / textureSize(image, 0);
    vec3 color = vec3(0.0);
    
    if (isVertical) {
        for (int i = 0; i < N; i++) {
            color += weights[i] * texture(image, uv + vec2(0.0, pixelOffset.y * (i-M))).rgb;
        }
    } else {
        for (int i = 0; i < N; i++) {
            color += weights[i] * texture(image, uv + vec2(pixelOffset.x * (i-M), 0.0)).rgb;
        }
    }
	// increase brightness slightly to get more glowy effect
    FragColor = vec4(1.1 * color, 1.0);
}