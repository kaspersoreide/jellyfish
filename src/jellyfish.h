#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class Jellyfish {
public:
    Jellyfish();
    void createGeometry();

    GLuint VAO;
    int numVertices;
};