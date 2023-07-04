#include "InputManager.h"

Camera* InputManager::camera = nullptr;
GLFWwindow* InputManager::window = nullptr;
bool InputManager::firstMouse = true;
bool InputManager::rightButtonPressed = false;
bool InputManager::autoRotate = false;
double InputManager::lastX = 0.0;
double InputManager::lastY = 0.0;

Player* InputManager::player = nullptr;

InputManager::InputManager(GLFWwindow* win, Camera* cam, Player* plr) {
    window = win;
    camera = cam;
    player = plr;  // Initialize the Player pointer
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void InputManager::update(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->moveForward(deltaTime);
        if (camera->isWalkingMode) player->position = camera->position;  // Update the Player position
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->moveBackward(deltaTime);
        if (camera->isWalkingMode) player->position = camera->position;  // Update the Player position
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->moveLeft(deltaTime);
        if (camera->isWalkingMode) player->position = camera->position;  // Update the Player position
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->moveRight(deltaTime);
        if (camera->isWalkingMode) player->position = camera->position;  // Update the Player position
    }

    camera->update(deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && camera->isWalkingMode && !camera->isJumping)
        camera->jump();

    if (camera->isWalkingMode) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void InputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!rightButtonPressed && !autoRotate && !camera->isWalkingMode) {
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
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && camera->isWalkingMode) {
        camera->jump();
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) { // C for Camera mode
        if (camera->isWalkingMode) {
            // switching from walking mode to free mode, save the current camera state
            camera->savedPosition = camera->position;
            camera->savedYaw = camera->yaw;
            camera->savedPitch = camera->pitch;
            rightButtonPressed = false; // Ensure right button is not pressed in free mode
            firstMouse = true; // reset mouse state
        }
        else {
            // switching from free mode to walking mode, restore the saved camera state
            camera->position = glm::vec3(camera->savedPosition.x, 1.5f, camera->savedPosition.z); // preserve x and z coordinates, adjust y
            camera->yaw = camera->savedYaw;
            camera->pitch = camera->savedPitch;
            camera->updateCameraVectors(); // update camera vectors after modifying yaw and pitch
            player->position = camera->position; // update player position when switching from free mode to walking mode
        }
        camera->isWalkingMode = !camera->isWalkingMode;
    }
}

void InputManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (!camera->isWalkingMode) {
        camera->processMouseScroll(yoffset);
    }
}