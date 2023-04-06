#pragma once
#include "GL/glew.h"
#include "loadshaders.h"

//helper enum for different texture types
enum FramebufferType {
    FB_FLOAT,
	FB_DEFAULT,
};

struct Framebuffer {
	Framebuffer(GLsizei width, GLsizei height, FramebufferType t);
	void bind(){ glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); }
	void unbind(){ glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	GLuint texture, depthbuffer, framebuffer;
};

