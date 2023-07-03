#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>


Window::Window(Camera* cam) {
    // initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int screenWidth = mode->width;
    int screenHeight = mode->height;

    int windowWidth = static_cast<int>(screenWidth * 0.6);
    int windowHeight = static_cast<int>(screenHeight * 0.6);
    int windowPosX = (screenWidth - windowWidth) / 2;
    int windowPosY = (screenHeight - windowHeight) / 2;

    // create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(windowWidth, windowHeight, "3D Engine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Set the window position
    glfwSetWindowPos(window, windowPosX, windowPosY);

    // make the window's context current
    glfwMakeContextCurrent(window);

    // set the framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    camera = cam;

    // set the initial viewport size
    setViewportSize(windowWidth, windowHeight);
}



Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::setViewportSize(int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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