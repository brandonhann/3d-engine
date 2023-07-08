#include "Chunk.h"

Chunk::Chunk(Shader& shader, float width, float length, glm::vec2 position)
    : shader(shader), width(width), length(length), scale(phi),
    position(glm::vec3(static_cast<float>(position.x), 0.0f, static_cast<float>(position.y))) {
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noiseGenerator.SetSeed(phi);
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
    const int chunkSize = 32;
    const int scale = static_cast<int>(phi);

    const int indicesPerQuad = 6;

    for (int z = 0; z < chunkSize - 1; ++z) {
        for (int x = 0; x < chunkSize - 1; ++x) {
            glm::vec3 v1(x * scale + position.x, getHeight(x * scale + position.x, z * scale + position.z), z * scale + position.z);
            glm::vec3 v2(x * scale + position.x, getHeight(x * scale + position.x, (z + 1) * scale + position.z), (z + 1) * scale + position.z);
            glm::vec3 v3((x + 1) * scale + position.x, getHeight((x + 1) * scale + position.x, z * scale + position.z), z * scale + position.z);
            glm::vec3 v4((x + 1) * scale + position.x, getHeight((x + 1) * scale + position.x, (z + 1) * scale + position.z), (z + 1) * scale + position.z);

            glm::vec3 normal1 = glm::normalize(glm::cross(v2 - v1, v3 - v1));
            glm::vec3 normal2 = glm::normalize(glm::cross(v3 - v2, v4 - v2));

            std::vector<glm::vec3> currentVertices = { v1, v2, v3, v2, v3, v4 };
            std::vector<glm::vec3> currentNormals = { normal1, normal1, normal1, normal2, normal2, normal2 };

            for (const auto& vertex : currentVertices) {
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);
            }

            for (const auto& normal : currentNormals) {
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
            }

            unsigned int vertexIndex = static_cast<unsigned int>((z * (chunkSize - 1) + x) * indicesPerQuad);
            std::vector<unsigned int> currentIndices = { vertexIndex, vertexIndex + 1, vertexIndex + 2, vertexIndex + 3, vertexIndex + 4, vertexIndex + 5 };
            indices.insert(indices.end(), currentIndices.begin(), currentIndices.end());
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
    return glm::vec3(width * scale, height * scale, length * scale);
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
