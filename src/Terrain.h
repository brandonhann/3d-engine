#pragma once
#include "Shader.h"
#include <GL/glew.h>
#include <vector>

class Terrain {
public:
    Terrain(Shader& shader, int width, int length);
    void generateVertices();
    void drawTerrain();
    float getHeight(float x, float z);
    int getWidth();
    int getLength();
    Shader& getShader();

private:
    Shader& shader;
    int width;
    int length;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;
};