#include "Terrain.h"
#include <GL/glew.h>

Terrain::Terrain(Shader& shader, int width, int length)
    : shader(shader), width(width), length(length), noiseGenerator(FastNoiseLite()) {

    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noiseGenerator.SetSeed(42);
    noiseGenerator.SetFrequency(0.02f);

    generateVertices();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() + normals.size()) * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), normals.size() * sizeof(float), &normals[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(vertices.size() * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void Terrain::generateVertices() {
    for (int z = 0; z < length; z++) {
        for (int x = 0; x < width; x++) {
            float y = getHeight(x, z);

            vertices.push_back((float)x);
            vertices.push_back(y);
            vertices.push_back((float)z);

            // Calculate normal here
            float heightLeft = getHeight(x - 1, z);
            float heightRight = getHeight(x + 1, z);
            float heightDown = getHeight(x, z - 1);
            float heightUp = getHeight(x, z + 1);

            glm::vec3 normal = glm::normalize(glm::vec3(heightLeft - heightRight, 2.0f, heightDown - heightUp));

            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
        }
    }

    for (int z = 0; z < length - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            // first triangle (top left, bottom left, top right)
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            // second triangle (top right, bottom left, bottom right)
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}

void Terrain::drawTerrain() {
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // use GL_TRIANGLES and draw elements using indices
    glBindVertexArray(0);
}

float Terrain::getHeight(float x, float z) {
    return 10.0f * noiseGenerator.GetNoise(x, z);
}

int Terrain::getWidth() {
    return this->width;
}

int Terrain::getLength() {
    return this->length;
}

Shader& Terrain::getShader() {
    return this->shader;
}