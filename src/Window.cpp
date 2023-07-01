#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

Window::Window(int width, int height, const char* title, Camera* cam) {
    // initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

    // initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    camera = cam;
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

GLFWwindow* Window::getWindow() {
    return window;
}

int Window::getWidth() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int Window::getHeight() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}
