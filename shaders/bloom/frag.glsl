#version 430 core

in vec2 uv;
out vec4 FragColor;

layout(location = 0) uniform sampler2D image;
layout(location = 1) uniform bool isVertical;

const float weights[5] = { 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 };

void main() {
    vec2 pixelOffset = 1.0 / textureSize(image, 0);
    vec3 color = vec3(0.0);
    if (isVertical) {
        for (int i = -5; i < 5; i++) {
            color += weights[abs(i)] * texture(image, uv + vec2(0.0, pixelOffset.y * i)).rgb;
        }
    } else {
        for (int i = -5; i < 5; i++) {
            color += weights[abs(i)] * texture(image, uv + vec2(pixelOffset.x * i, 0.0)).rgb;
        }
    }
    FragColor = vec4(color, 1.0);
}