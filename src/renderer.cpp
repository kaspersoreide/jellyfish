#include "renderer.h"

Renderer::Renderer() {
    jellyfishShader = loadShaders("shaders/jellyfish/vert.glsl", "shaders/jellyfish/frag.glsl");
    bloomShader = loadShaders("shaders/bloom/vert.glsl", "shaders/bloom/frag.glsl");
    framebufferShader = loadShaders("shaders/framebuffer/vert.glsl", "shaders/bloom/frag.glsl");

    buffers[0] = new Framebuffer(1920, 1080, FB_FLOAT);
    buffers[1] = new Framebuffer(1920, 1080, FB_FLOAT);

    //gen screen quad VAO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	float data[] = {
		1.0, -1.0,
		1.0, 1.0,
		-1.0, 1.0,
		1.0, -1.0,
		-1.0, -1.0,
		-1.0, 1.0,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data[0], GL_STATIC_DRAW);
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(float),
		(void*)0
	);
}

void Renderer::swapBuffers() {
    Framebuffer* tmp = buffers[0];
    buffers[0] = buffers[1];
    buffers[1] = tmp;
}

void Renderer::drawFullscreenQuad() {
	glBindVertexArray(quadVAO);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::bloom() {
    glUseProgram(bloomShader);
    
    //set to vertical smoothing
    glUniform1i(1, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, buffers[1]->framebuffer);
    glBindTexture(GL_TEXTURE_2D, buffers[0]->texture);
    drawFullscreenQuad();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    swapBuffers();
    
    //horizontal smoothing
    glUniform1i(1, 1);
    glBindFramebuffer(GL_FRAMEBUFFER, buffers[1]->framebuffer);
    glBindTexture(GL_TEXTURE_2D, buffers[0]->texture);
    drawFullscreenQuad();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    swapBuffers();   
}

void Renderer::renderJellyfish(Jellyfish* jellyfish, glm::mat4 VP, float t) {
    glUseProgram(jellyfishShader);
    glBindVertexArray(jellyfish->VAO);
    glUniformMatrix4fv(0, 1, GL_FALSE, &VP[0][0]);
    glUniform1f(1, t);
    glPointSize(2.0f);
    glDrawArrays(GL_POINTS, 0, jellyfish->numVertices);
}

void Renderer::renderToScreen(bool bloomEnabled) {
    if (bloomEnabled) {
        bloom();
    }
    glBlitNamedFramebuffer(
        buffers[0]->framebuffer, 0,
        0, 0, 1920, 1080,
        0, 0, 1920, 1080,
        GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
        GL_NEAREST
    );
    //glUseProgram(framebufferShader);
    //buffers[0]->unbind();
    //glBindTexture(GL_TEXTURE_2D, buffers[0]->texture);
    //glUniform1i(0, 0);
    //drawFullscreenQuad();
} 