#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "player/Camera.h"

class Window {
public:
    Window(Camera* cam);
    int getWidth();
    int getHeight();
    ~Window();
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    GLFWwindow* getWindow();
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
    GLFWwindow* window;
    Camera* camera;
    void setViewportSize(int width, int height);
};
