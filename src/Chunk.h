#pragma once
#include "Terrain.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Chunk {
public:
    Chunk(Terrain& terrain, glm::vec2 position);
    void generateVertices();
    void drawChunk(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    //float getHeight(float x, float z);

private:
    Terrain& terrain;
    glm::vec2 position;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> normals;
    GLuint VAO, VBO, EBO;
};