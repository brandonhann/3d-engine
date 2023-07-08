#ifndef CHUNK_H
#define CHUNK_H

#include "../shaders/Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "FastNoiseLite.h"
#include "../Config.h"

class Chunk {
public:
    Chunk(Shader& shader, float width, float length, glm::vec2 position);
    void generateVertices();
    void drawChunk(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    glm::vec3 getBoundingBox();
    glm::vec3 getMin();
    glm::vec3 getMax();
    float getHeight(float x, float z);
    float getWidth();
    float getLength();
    Shader& getShader();
    Config config;
    float phi = config.phi;

private:
    Shader& shader;
    float width = 100.0f;
    float length = 100.0f;
    float scale;
    glm::vec3 position;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> normals;
    GLuint VAO, VBO, EBO;
    FastNoiseLite noiseGenerator;

    float interpolate(float a, float b, float fraction);
};

#endif
