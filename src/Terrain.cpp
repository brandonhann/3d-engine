#include "Terrain.h"
#include <GL/glew.h>

Terrain::Terrain(Shader& shader, int width, int length) : shader(shader), width(width), length(length) {
    generateVertices();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO); // generate EBO for indices

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // bind and set indices data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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
    // TODO implement this function. for now, return 0.
    return 0;
}

int Terrain::getWidth() {
    // return the width
    return this->width;
}

int Terrain::getLength() {
    // return the length
    return this->length;
}

Shader& Terrain::getShader() {
    // return the shader
    return this->shader;
}
