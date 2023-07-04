#include "GameLoop.h"
#include <iostream>
#include <thread>
#include <chrono>

GameLoop::GameLoop(Window* window, Camera* camera, Player* player, InputManager* inputManager, Shader* shader, Terrain* terrain, Chunk* chunk, GuiManager* guiManager)
    : window(window), camera(camera), player(player), inputManager(inputManager), shader(shader), terrain(terrain), chunk(chunk), guiManager(guiManager), sensor(*player, *chunk) {
}

void GameLoop::run() {
    float lastFrame = 0.0f;
    float lastSecond = 0.0f; // Track the last time one second has passed
    int frames = 0; // Track the number of frames rendered

    const float targetFPS = 65.0f;
    const float targetFrameTime = 1.0f / targetFPS;

    while (!window->shouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;

        if (deltaTime < targetFrameTime) {
            float sleepTime = targetFrameTime - deltaTime;
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(sleepTime * 1000.0f)));
            currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
        }

        lastFrame = currentFrame;

        guiManager->renderFPS(); // ImGui rendering

        window->swapBuffers();
        window->pollEvents();

        if (currentFrame - lastSecond >= 1.0f) { // If at least one second has passed
            frames = 0; // Reset the frame counter
            lastSecond = currentFrame; // Reset the last second tracker
        }

        inputManager->update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double aspectRatio = ((double)window->getWidth()) / window->getHeight();

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera->zoom), (float)aspectRatio, 0.1f, 200.0f);
        shader->setMat4("projection", projectionMatrix);

        glm::mat4 viewMatrix = camera->getViewMatrix();
        shader->setMat4("view", viewMatrix);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        shader->setMat4("model", modelMatrix);

        if (!camera->isWalkingMode) {
            player->draw(*shader, viewMatrix, projectionMatrix);
        }

        shader->setVec4("objectColor", glm::vec4(0.0f, 5.0f, 0.0f, 1.0f)); // green color for the chunk
        chunk->drawChunk(modelMatrix, viewMatrix, projectionMatrix);

        sensor.update();

        frames++; // Increment the frame counter
    }
}
