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
    int n = 1000;
    const float goldenRatio = 0.5f * (1.0f + sqrtf(5.0f));
    for (int i = 0; i < n; i++) {
        float theta = 2 * PI * i / goldenRatio;
        float phi = acosf(1.0f - 2.0f * (i + 0.5f) / n);
        vec3 vertex = { cosf(theta) * sinf(phi), sinf(theta) * sinf(phi), cosf(phi) };
        if (vertex.z > 0.05 * sinf(8 * theta)) {
            vertices.push_back(vertex);
            vertices.push_back({90.0f / 255, 134.0f / 255, 1.5f + sinf(12 * theta) + 173.0f / 255});
        }
    }
    //generate "arms"
    const int numArms = 8;
    const int k = 90;
    for (int i = 0; i < numArms; i++) {
        float angle = i * 2.0 * PI / numArms;
        float x = 0.8 * cosf(angle);
        float y = 0.8 * sinf(angle);
        for (int j = 0; j < k; j++) {
            float z = - 4.0 * float(j) / k;
            vertices.push_back({ x, y, z });
            vertices.push_back({1.5, 1.2, 1.8});
        }
    }
    VAO = vertexArray2x3f(vertices);
    numVertices = vertices.size();
}