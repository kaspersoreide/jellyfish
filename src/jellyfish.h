#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

class Jellyfish {
public:
    Jellyfish();
    void createGeometry();

    GLuint VAO;
    int numVertices;
};