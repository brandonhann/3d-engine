#ifndef GRID_H
#define GRID_H

#include "Shader.h"

class Grid {
public:
    Grid(Shader& shader, float width, float length, float cellSize);
    void drawGrid();

private:
    Shader& shader;
    float width;
    float length;
    float cellSize;
    GLuint VAO, VBO;
};

#endif