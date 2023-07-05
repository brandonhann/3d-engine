#include "Chunk.h"

Chunk::Chunk(Shader& shader, int width, int length, glm::vec2 position)
    : shader(shader), width(width), length(length), noiseGenerator(FastNoiseLite()), position(glm::vec3(position.x, 0, position.y)) {
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

void Chunk::generateVertices() {
    int chunkSize = 16; // Size of chunk
    float scale = 3.5f; // This can be adjusted to your liking

    for (int z = 0; z < chunkSize - 1; z++) {
        for (int x = 0; x < chunkSize - 1; x++) {
            glm::vec3 v1((float)x * scale + position.x, getHeight(x * scale + position.x, z * scale + position.z), (float)z * scale + position.z);
            glm::vec3 v2((float)x * scale + position.x, getHeight(x * scale + position.x, (z + 1) * scale + position.z), (float)(z + 1) * scale + position.z);
            glm::vec3 v3((float)(x + 1) * scale + position.x, getHeight((x + 1) * scale + position.x, z * scale + position.z), (float)z * scale + position.z);
            glm::vec3 v4((float)(x + 1) * scale + position.x, getHeight((x + 1) * scale + position.x, (z + 1) * scale + position.z), (float)(z + 1) * scale + position.z);

            // Calculate normal for first triangle (v1, v2, v3)
            glm::vec3 normal1 = glm::normalize(glm::cross(v2 - v1, v3 - v1));
            // Calculate normal for second triangle (v2, v3, v4)
            glm::vec3 normal2 = glm::normalize(glm::cross(v3 - v2, v4 - v2));

            // first triangle vertices
            vertices.insert(vertices.end(), { v1.x, v1.y, v1.z });
            vertices.insert(vertices.end(), { v2.x, v2.y, v2.z });
            vertices.insert(vertices.end(), { v3.x, v3.y, v3.z });

            // first triangle normals
            for (int i = 0; i < 3; i++) {
                normals.insert(normals.end(), { normal1.x, normal1.y, normal1.z });
            }

            // second triangle vertices
            vertices.insert(vertices.end(), { v2.x, v2.y, v2.z });
            vertices.insert(vertices.end(), { v3.x, v3.y, v3.z });
            vertices.insert(vertices.end(), { v4.x, v4.y, v4.z });

            // second triangle normals
            for (int i = 0; i < 3; i++) {
                normals.insert(normals.end(), { normal2.x, normal2.y, normal2.z });
            }

            // indices - each triangle has its own set of vertices now
            unsigned int vertexIndex = static_cast<unsigned int>((z * (chunkSize - 1) + x) * 6);  // 6 vertices per quad (2 triangles)
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
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::vec3 Chunk::getMin() {
    return position; // The minimum point is the position itself
}

glm::vec3 Chunk::getMax() {
    return position + getBoundingBox(); // The maximum point is position + dimensions
}

glm::vec3 Chunk::getBoundingBox() {
    int height = 1; // Replace with your chunk's height
    return glm::vec3(width, height, length);
}

float Chunk::getHeight(float x, float z) {
    int xInt = (int)x;
    int zInt = (int)z;

    float fracX = x - xInt;
    float fracZ = z - zInt;

    float h00 = getRawHeight(xInt, zInt);
    float h10 = getRawHeight(xInt + 1, zInt);
    float h01 = getRawHeight(xInt, zInt + 1);
    float h11 = getRawHeight(xInt + 1, zInt + 1);

    float heightX1 = interpolate(h00, h10, fracX);
    float heightX2 = interpolate(h01, h11, fracX);
    float height = interpolate(heightX1, heightX2, fracZ);

    return height;
}

float Chunk::getRawHeight(float x, float z) {
    float rawHeight = noiseGenerator.GetNoise(x, z);

    // Adjust the multiplier to change the amplitude of the terrain
    rawHeight *= 10.0f;

    // Use a step function to make the terrain less smooth and more angular
    float stepSize = 1.0f; // Adjust this to change the size of the "steps"
    float steppedHeight = std::round(rawHeight / stepSize) * stepSize;

    return steppedHeight;
}

float Chunk::interpolate(float a, float b, float fraction) {
    return a + fraction * (b - a);
}

int Chunk::getWidth() {
    return this->width;
}

int Chunk::getLength() {
    return this->length;
}

Shader& Chunk::getShader() {
    return this->shader;
}