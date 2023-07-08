#include "Game.h"
#include "GameLoop.h"
#include "terrain/Chunk.h"
#include "shaders/Lighting.h"

Game::Game()
    : window(&camera),
    shader("./src/glsl/VertexShader.glsl", "./src/glsl/FragmentShader.glsl"),
    player(), // Instantiate the Player object
    camera(player), // Pass the Player object reference to the Camera constructor
    inputManager(window.getWindow(), &camera, &player, &chunk),
    chunk(shader, 100.0f, 100.0f, glm::vec2(0, 0)),
    guiManager(window.getWindow()),
    gameLoop(&window, &camera, &player, &inputManager, &shader, &chunk, &guiManager) {
    shader.use();

    Lighting sunLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sunLight.setLight(shader);
    glEnable(GL_DEPTH_TEST);
}

Game::~Game() {
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Game::run() {
    while (!window.shouldClose()) {
        if (glfwGetWindowAttrib(window.getWindow(), GLFW_ICONIFIED)) {
            // If the window is minimized, don't perform rendering
            continue;
        }
        gameLoop.run();
    }
}

int main() {
    Game game;
    game.run();
    return 0;
}
