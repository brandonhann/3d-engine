#include "InputManager.h"

Camera* InputManager::camera = nullptr;
GLFWwindow* InputManager::window = nullptr;
bool InputManager::firstMouse = true;
bool InputManager::rightButtonPressed = false;
bool InputManager::autoRotate = false;
double InputManager::lastX = 0.0;
double InputManager::lastY = 0.0;

InputManager::InputManager(GLFWwindow* win, Camera* cam) {
    window = win;
    camera = cam;
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
}

void InputManager::update(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveRight(deltaTime);
}

void InputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!rightButtonPressed && !autoRotate) {
        return;
    }

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

void InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            rightButtonPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            rightButtonPressed = false;
            firstMouse = true; // reset mouse state
        }
    }
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        autoRotate = !autoRotate;
    }
}
