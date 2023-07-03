#ifndef TERRAIN_H
#define TERRAIN_H

#include "Shader.h"
#include <vector>

class Terrain {
public:
    Terrain(Shader& shader, int width, int length);
    void drawTerrain();
    float getHeight(float x, float z);

private:
    Shader& shader;
    int width;
    int length;
    GLuint VAO, VBO;
    std::vector<float> vertices;
    void generateVertices();
};

#endif