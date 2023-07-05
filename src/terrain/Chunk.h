#ifndef CHUNK_H
#define CHUNK_H

#include "../shaders/Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "FastNoiseLite.h"

class Chunk {
public:
    Chunk(Shader& shader, int width, int length, glm::vec2 position);
    void generateVertices();
    void drawChunk(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    glm::vec3 getBoundingBox();
    glm::vec3 getMin();
    glm::vec3 getMax();
    float getHeight(float x, float z);
    int getWidth();
    int getLength();
    Shader& getShader();

private:
    Shader& shader;
    int width = 100.0f;
    int length = 100.0f;
    glm::vec3 position;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> normals;
    GLuint VAO, VBO, EBO;
    FastNoiseLite noiseGenerator;

    float getRawHeight(float x, float z);
    float interpolate(float a, float b, float fraction);
};

#endif
