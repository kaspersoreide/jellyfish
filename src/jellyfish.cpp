#include "jellyfish.h"
#include <math.h>
#include <vector>
#include <vertexarrays.h>
#include "loadshaders.h"
#define PI 3.14159265358979323846

using namespace glm;
using namespace std;

Jellyfish::Jellyfish() {
    createGeometry();
}

void Jellyfish::createGeometry() {

    //generate points on a sphere by using fibonacci sphere algorithm
    vector<vec3> vertices;
    int n = 1200;
    const float goldenRatio = 0.5f * (1.0f + sqrtf(5.0f));
    for (int i = 0; i < n; i++) {
        float theta = 2 * PI * i / goldenRatio;
        float phi = acosf(1.0f - 2.0f * (i + 0.5f) / n);
        vec3 vertex = { cosf(theta) * sinf(phi), sinf(theta) * sinf(phi), cosf(phi) };
        if (vertex.z > 0.1 * sinf(12 * theta)) {
            vertices.push_back(vertex);
            vertices.push_back({1.0f, 1.0f, 1.0f});
        }
    }
    VAO = vertexArray2x3f(vertices);
    numVertices = vertices.size();
}