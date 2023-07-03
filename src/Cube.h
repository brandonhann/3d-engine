#pragma once
#include "Shader.h"
#include <GL/glew.h>

class Cube {
public:
    Cube(Shader& shader);
    ~Cube();
    void drawCube();

private:
    Shader& shader;
    GLuint VAO, VBO, EBO; // Add an element buffer for the cube
    GLuint texture1, texture2; // Textures for the cube

    void setupMesh();
};
