#pragma once
#include "jellyfish.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Renderer {
public:
    Renderer();
    GLuint bloomShader, jellyfishShader, screenShader, copyShader;
    GLuint quadVAO;
    GLuint hdrFBO;
    GLuint colorBuffer;
    GLuint pingpongFBO[2];
    GLuint pingpongTextures[2];
    void copyFramebuffer(GLuint src, GLuint dst);
    void drawFullscreenQuad();
    void bloom();
    void renderJellyfish(Jellyfish* jellyfish, glm::mat4 VP, float t);
    void renderToScreen();
    void clear();
};

extern Renderer* renderer;