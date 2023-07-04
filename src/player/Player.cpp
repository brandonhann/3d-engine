#include "Player.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h> 

Player::Player() : position(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 2.0f, 1.0f)) {}

void Player::draw(Shader& shader, glm::mat4& view, glm::mat4& projection) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    shader.setMat4("model", model);
    shader.setVec4("objectColor", glm::vec4(10.0f, 10.0f, 10.0f, 1.0f));

    // Define the player as a simple 3D cuboid for now
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, // front bottom-left corner
         0.5f, -0.5f, -0.5f, // front bottom-right corner
         0.5f,  0.5f, -0.5f, // front top-right corner
        -0.5f,  0.5f, -0.5f, // front top-left corner
        -0.5f, -0.5f,  0.5f, // back bottom-left corner
         0.5f, -0.5f,  0.5f, // back bottom-right corner
         0.5f,  0.5f,  0.5f, // back top-right corner
        -0.5f,  0.5f,  0.5f  // back top-left corner
    };

    unsigned int indices[] = {
        0, 1, 2, // front face
        2, 3, 0, // front face
        4, 5, 6, // back face
        6, 7, 4, // back face
        0, 1, 5, // bottom face
        5, 4, 0, // bottom face
        3, 2, 6, // top face
        6, 7, 3, // top face
        0, 4, 7, // left face
        7, 3, 0, // left face
        1, 5, 6, // right face
        6, 2, 1  // right face
    };


    // Create VAO, VBO and EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Render the player
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Cleanup after rendering
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

glm::vec3 Player::getMin() {
    return position - scale * 0.5f;
}

glm::vec3 Player::getMax() {
    return position + scale * 0.5f;
}