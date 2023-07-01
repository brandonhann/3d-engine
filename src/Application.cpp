#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/ext.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Cube.h"
#include "Camera.h"
#include <iostream>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string readShaderFile(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint loadShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string vertexShaderSource = readShaderFile(vertexShaderPath);
    std::string fragmentShaderSource = readShaderFile(fragmentShaderPath);
    const char* pVertexSource = vertexShaderSource.c_str();
    const char* pFragmentSource = fragmentShaderSource.c_str();
    glShaderSource(vertexShader, 1, &pVertexSource, NULL);
    glShaderSource(fragmentShader, 1, &pFragmentSource, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    // initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "3D Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

    // initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // compile and link shaders
    GLuint shaderProgram = loadShader("./src/glsl/VertexShader.glsl", "./src/glsl/FragmentShader.glsl");
    glUseProgram(shaderProgram);


    // enable depth test
    glEnable(GL_DEPTH_TEST);

    double aspectRatio = ((double)640) / 480; // window width / height
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)aspectRatio, 0.1f, 100.0f);
    // use the handle of the uniform location in the shader program for the projection matrix
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    if (projLoc != -1) {
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }
    else {
        std::cerr << "Failed to find projection uniform in shader" << std::endl;
    }



    Cube cube;

    Camera camera;

    while (!glfwWindowShouldClose(window)) {
        float deltaTime = glfwGetTime();
        glfwSetTime(0.0);

        // camera controls
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.moveForward(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.moveBackward(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.moveLeft(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.moveRight(deltaTime);

        glm::mat4 viewMatrix = camera.getViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube.drawCube();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}