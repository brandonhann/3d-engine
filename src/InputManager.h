#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include "Camera.h"

class InputManager {
public:
    InputManager(GLFWwindow* window, Camera* camera);

    void update(float deltaTime);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    static Camera* camera;
    static GLFWwindow* window;
    static bool firstMouse;
    static bool rightButtonPressed;
    static bool autoRotate;
    static double lastX;
    static double lastY;
};

#endif