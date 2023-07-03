#include "Terrain.h"
#include <GL/glew.h>

Terrain::Terrain(Shader& shader, int width, int length) : shader(shader), width(width), length(length) {
    generateVertices();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Terrain::generateVertices() {
    for (int z = 0; z < length; z++) {
        for (int x = 0; x < width; x++) {
            float y = getHeight(x, z);

            vertices.push_back((float)x);
            vertices.push_back(y);
            vertices.push_back((float)z);
        }
    }
}

void Terrain::drawTerrain() {
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, width * length);
    glBindVertexArray(0);
}

float Terrain::getHeight(float x, float z) {
    // Replace this with your own Perlin noise function
    return 0.0f; // flat terrain
}