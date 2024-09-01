#include "jellyfish.h"
#include <math.h>
#include <vector>
//#include <vertexarrays.h>
#include "glutils.hpp"
#define PI 3.14159265358979323846

using namespace glm;
using namespace std;

Jellyfish::Jellyfish() {
    createGeometry();
}

void Jellyfish::createGeometry() {

    vector<vec3> vertices, colors;
    const int numBands = 10;
    const int density = 80;
    const int ringDensity = 8 * density;
    const float ringHeight = 0.1f;
    //generate the top of the head with bands going down a half-sphere
    for (int i = 0; i < numBands; i++) {
        float theta = 2 * i * PI / numBands;
        for (int j = 0; j < density; j++) {
            float phi = j * 0.5f * PI / density;
            vertices.push_back({cosf(theta) * sinf(phi), sinf(theta) * sinf(phi), cosf(phi) - ringHeight});
            colors.push_back({10.0f / 255, 84.0f / 255, 1.5f + sinf(12 * theta)});
        }
    }
    //make a sine wave in a ring around the head
    for (int i = 0; i < ringDensity; i++) {
        float theta = 2 * i * PI / ringDensity;
        float heightFreq = numBands * 2 * i * PI / ringDensity;
        vertices.push_back({cosf(theta), sinf(theta), ringHeight * cosf(heightFreq + PI)});
        colors.push_back({90.0f / 255, 134.0f / 255, 1.5f + sinf(12 * theta) + 173.0f / 255});
    }
    //generate arms
    const int numArms = 8;
    const int k = 80;
    for (int i = 0; i < numArms; i++) {
        float angle = i * 2.0 * PI / numArms;
        float x = 0.8 * cosf(angle);
        float y = 0.8 * sinf(angle);
        for (int j = 0; j < k; j++) {
            float z = - 3.0 * float(j) / k;
            vertices.push_back({ x, y, z });
            colors.push_back({1.0, 57.0f / 255, 64.0 / 255});
        }
    }
    //VAO = vertexArray2x3f(vertices);
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
    generateAttribute(0, 3, vertices, false);
    generateAttribute(1, 3, colors, false);
    numVertices = vertices.size();
}