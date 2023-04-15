#pragma once
#include "framebuffer.h"
#include "jellyfish.h"

class Renderer {
public:
    Renderer();
    GLuint bloomShader, jellyfishShader, screenShader, copyShader;
    GLuint quadVAO;
    Framebuffer* buffers[2];
    GLuint hdrFBO;
    GLuint colorBuffers[2];
    GLuint pingpongFBO[2];
    GLuint pingpongTextures[2];
    void copyFramebuffer(GLuint src, GLuint dst);
    void drawFullscreenQuad();
    void swapBuffers();
    void bloom();
    void renderJellyfish(Jellyfish* jellyfish, glm::mat4 VP, float t);
    void renderToScreen(bool bloomEnabled = false);
    void clear();
};

extern Renderer* renderer;