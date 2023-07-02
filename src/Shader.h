#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    GLuint getProgramID();
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec4(const std::string& name, const glm::vec4& vec) const;

private:
    std::string readShaderFile(const char* filePath);
    GLuint loadShader(const char* vertexShaderPath, const char* fragmentShaderPath);
    GLuint shaderID;
};