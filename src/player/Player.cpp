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

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, // bottom left front
         0.5f, -0.5f, -0.5f, // bottom right front
         0.0f,  0.5f, -0.5f, // top center front
        -0.5f, -0.5f,  0.5f, // bottom left back
         0.5f, -0.5f,  0.5f, // bottom right back
         0.0f,  0.5f,  0.5f  // top center back
    };

    unsigned int indices[] = {
        0, 1, 2, // front face
        3, 4, 5, // back face
        0, 1, 4, // bottom face
        4, 3, 0, // bottom face
        0, 2, 5, // left face
        5, 3, 0, // left face
        1, 2, 5, // right face
        5, 4, 1  // right face
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