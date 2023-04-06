#pragma once
#include "framebuffer.h"
#include "jellyfish.h"

class Renderer {
public:
    Renderer();
    GLuint bloomShader, jellyfishShader, framebufferShader;
    GLuint quadVAO;
    Framebuffer* buffers[2];
    void drawFullscreenQuad();
    void swapBuffers();
    void bloom();
    void renderJellyfish(Jellyfish* jellyfish, glm::mat4 VP);
    void renderToScreen(bool bloomEnabled = false);
};

extern Renderer* renderer;