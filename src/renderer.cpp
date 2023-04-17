#include "renderer.h"
#include "loadshaders.h"

Renderer::Renderer() {
    jellyfishShader = loadShaders("shaders/jellyfish/vert.glsl", "shaders/jellyfish/frag.glsl");
    bloomShader = loadShaders("shaders/bloom/vert.glsl", "shaders/bloom/frag.glsl");
    screenShader = loadShaders("shaders/screen/vert.glsl", "shaders/screen/frag.glsl");
    copyShader = loadShaders("shaders/copy/vert.glsl", "shaders/copy/frag.glsl");

    
    // make hdr framebuffer with 2 color attachments
    // 1 for dark and 1 for bright colors
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glGenTextures(1, &colorBuffer);

    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // attach texture to framebuffer
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0
    );
    
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    
    
    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongTextures);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongTextures[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongTextures[i], 0
        );
        // also check if framebuffers are complete (no need for depth buffer)
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    }
    

    //make screen quad VAO
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

void Renderer::copyFramebuffer(GLuint srcTexture, GLuint dstFramebuffer) {
    glUseProgram(copyShader);
    glBindTexture(GL_TEXTURE_2D, srcTexture);
    glBindFramebuffer(GL_FRAMEBUFFER, dstFramebuffer);
    drawFullscreenQuad();
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
    glActiveTexture(GL_TEXTURE0);
    //set to vertical smoothing
    glUniform1i(1, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[1]);
    glBindTexture(GL_TEXTURE_2D, pingpongTextures[0]);
    drawFullscreenQuad();
    
    //horizontal smoothing
    glUniform1i(1, 1);
    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[0]);
    glBindTexture(GL_TEXTURE_2D, pingpongTextures[1]);
    drawFullscreenQuad();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0); 
}

void Renderer::clear() {
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderJellyfish(Jellyfish* jellyfish, glm::mat4 VP, float t) {
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glUseProgram(jellyfishShader);
    glBindVertexArray(jellyfish->VAO);
    glUniformMatrix4fv(0, 1, GL_FALSE, &VP[0][0]);
    glUniform1f(1, t);
    glPointSize(2.0f);
    glDrawArrays(GL_POINTS, 0, jellyfish->numVertices);
}

void Renderer::renderToScreen() {
    copyFramebuffer(colorBuffer, pingpongFBO[0]);
    for (int i = 0; i < 5; i++) bloom();
    
    glUseProgram(screenShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glActiveTexture(GL_TEXTURE1);
    glUniform1i(1, 1);
    glBindTexture(GL_TEXTURE_2D, pingpongTextures[0]);
    drawFullscreenQuad();
    glActiveTexture(GL_TEXTURE0);
    
} 