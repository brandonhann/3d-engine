#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

class Lighting {
public:
    Lighting(const glm::vec3& lightPos, const glm::vec4& lightColor)
        : lightPos(lightPos), lightColor(lightColor) {}
    void setLight(Shader& shader) const {
        shader.setVec3("lightPos", lightPos);
        shader.setVec4("lightColor", lightColor);
    }
private:
    glm::vec3 lightPos;
    glm::vec4 lightColor;
};