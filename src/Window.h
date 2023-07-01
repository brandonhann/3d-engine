#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    int getWidth();
    int getHeight();
    ~Window();
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    GLFWwindow* getWindow();

private:
    GLFWwindow* window;
};