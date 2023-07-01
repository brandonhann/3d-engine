#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

class Window {
public:
    Window(int width, int height, const char* title, Camera* cam);
    int getWidth();
    int getHeight();
    ~Window();
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    GLFWwindow* getWindow();

private:
    GLFWwindow* window;
    Camera* camera;
};