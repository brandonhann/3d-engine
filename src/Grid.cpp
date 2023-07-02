#include "Grid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <vector>

Grid::Grid(Shader& shader, float width, float length, float cellSize)
    : shader(shader), width(width), length(length), cellSize(cellSize)
{
    std::vector<GLfloat> vertices;

    // vertices for lines along x-axis
    for (float i = -length / 2; i <= length / 2; i += cellSize) {
        vertices.push_back(-width / 2);
        vertices.push_back(0.0f);
        vertices.push_back(i);

        vertices.push_back(width / 2);
        vertices.push_back(0.0f);
        vertices.push_back(i);
    }

    // vertices for lines along z-axis
    for (float i = -width / 2; i <= width / 2; i += cellSize) {
        vertices.push_back(i);
        vertices.push_back(0.0f);
        vertices.push_back(-length / 2);

        vertices.push_back(i);
        vertices.push_back(0.0f);
        vertices.push_back(length / 2);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Grid::drawGrid() {
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, GLsizei((width / cellSize + length / cellSize) * 4));
    glBindVertexArray(0);
}
