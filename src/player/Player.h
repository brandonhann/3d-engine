#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "../shaders/Shader.h"

class Player {
public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 savedPosition;

    Player();
    void draw(Shader& shader, glm::mat4& view, glm::mat4& projection);
    glm::vec3 getMin();
    glm::vec3 getMax();
};

#endif