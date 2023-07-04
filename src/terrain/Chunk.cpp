#include "Chunk.h"

Chunk::Chunk(Terrain& terrain, glm::vec2 position)
    : terrain(terrain), position(glm::vec3(position.x, 0, position.y)) {
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
    int width = terrain.getWidth();
    int length = terrain.getLength();

    for (int z = 0; z < length; z++) {
        for (int x = 0; x < width; x++) {
            float y = terrain.getHeight(x + position.x, z + position.y);

            vertices.push_back((float)x + position.x);
            vertices.push_back(y);
            vertices.push_back((float)z + position.y);

            // Calculate normal here
            float heightLeft = terrain.getHeight(x - 1 + position.x, z + position.y);
            float heightRight = terrain.getHeight(x + 1 + position.x, z + position.y);
            float heightDown = terrain.getHeight(x + position.x, z - 1 + position.y);
            float heightUp = terrain.getHeight(x + position.x, z + 1 + position.y);

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

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}

void Chunk::drawChunk(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
    terrain.getShader().use();
    terrain.getShader().setMat4("model", model);
    terrain.getShader().setMat4("view", view);
    terrain.getShader().setMat4("projection", projection);

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
    // The function should return the dimensions of the bounding box for the chunk.
    // For a simple implementation, we're assuming each chunk is a cuboid with a width and length
    // equal to the Terrain's width and length, and a fixed height. Adjust this if your chunks are different.
    int width = terrain.getWidth();
    int length = terrain.getLength();
    int height = 1; // Replace with your chunk's height
    return glm::vec3(width, height, length);
}