#include "Chunk.h"

Chunk::Chunk(Shader& shader, float width, float length, glm::vec2 position)
    : shader(shader), width(width), length(length), noiseGenerator(FastNoiseLite()), position(glm::vec3(static_cast<float>(position.x), 0.0f, static_cast<float>(position.y))) {
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noiseGenerator.SetSeed(42);
    noiseGenerator.SetFrequency(0.02f);

    generateVertices();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    GLsizei bufferSize = static_cast<GLsizei>((vertices.size() + normals.size()) * sizeof(float));
    glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), normals.size() * sizeof(float), &normals[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(vertices.size() * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


void Chunk::generateVertices() {
    int chunkSize = 32;
    int scale = static_cast<int>(phi);

    for (int z = 0; z < chunkSize - 1; z++) {
        for (int x = 0; x < chunkSize - 1; x++) {
            glm::vec3 v1(static_cast<float>(x * scale + position.x), getHeight(static_cast<float>(x * scale + position.x), static_cast<float>(z * scale + position.z)), static_cast<float>(z * scale + position.z));
            glm::vec3 v2(static_cast<float>(x * scale + position.x), getHeight(static_cast<float>(x * scale + position.x), static_cast<float>((z + 1) * scale + position.z)), static_cast<float>((z + 1) * scale + position.z));
            glm::vec3 v3(static_cast<float>((x + 1) * scale + position.x), getHeight(static_cast<float>((x + 1) * scale + position.x), static_cast<float>(z * scale + position.z)), static_cast<float>(z * scale + position.z));
            glm::vec3 v4(static_cast<float>((x + 1) * scale + position.x), getHeight(static_cast<float>((x + 1) * scale + position.x), static_cast<float>((z + 1) * scale + position.z)), static_cast<float>((z + 1) * scale + position.z));

            glm::vec3 normal1 = glm::normalize(glm::cross(v2 - v1, v3 - v1));
            glm::vec3 normal2 = glm::normalize(glm::cross(v3 - v2, v4 - v2));

            vertices.insert(vertices.end(), { v1.x, v1.y, v1.z });
            vertices.insert(vertices.end(), { v2.x, v2.y, v2.z });
            vertices.insert(vertices.end(), { v3.x, v3.y, v3.z });

            for (int i = 0; i < 3; i++) {
                normals.insert(normals.end(), { normal1.x, normal1.y, normal1.z });
            }

            vertices.insert(vertices.end(), { v2.x, v2.y, v2.z });
            vertices.insert(vertices.end(), { v3.x, v3.y, v3.z });
            vertices.insert(vertices.end(), { v4.x, v4.y, v4.z });

            for (int i = 0; i < 3; i++) {
                normals.insert(normals.end(), { normal2.x, normal2.y, normal2.z });
            }

            unsigned int vertexIndex = static_cast<unsigned int>((z * (chunkSize - 1) + x) * 6);
            indices.insert(indices.end(), { vertexIndex, vertexIndex + 1, vertexIndex + 2, vertexIndex + 3, vertexIndex + 4, vertexIndex + 5 });
        }
    }
}

void Chunk::drawChunk(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::vec3 Chunk::getMin() {
    return position; // The minimum point is the position itself
}

glm::vec3 Chunk::getMax() {
    return position + getBoundingBox(); // The maximum point is position + dimensions
}

glm::vec3 Chunk::getBoundingBox() {
    int height = static_cast<int>(phi); // Chunks height
    return glm::vec3(width, height, length);
}

float Chunk::getHeight(float x, float z) {
    float rawHeight = noiseGenerator.GetNoise(x, z);
    rawHeight *= 10.0f;
    float stepSize = 0.6f;
    float steppedHeight = round(rawHeight / stepSize) * stepSize;
    return steppedHeight;
}

float Chunk::interpolate(float a, float b, float fraction) {
    return a + fraction * (b - a);
}

float Chunk::getWidth() {
    return this->width;
}

float Chunk::getLength() {
    return this->length;
}

Shader& Chunk::getShader() {
    return this->shader;
}
