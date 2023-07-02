#ifndef CUBE_H
#define CUBE_H

#include "Shader.h"
#include <GL/glew.h>

class Cube {
private:
    Shader& shader;
    GLuint VAO, VBO;
public:
    Cube(Shader& shader);
    ~Cube();
    void drawCube();
    void setupCube();
};

#endif
