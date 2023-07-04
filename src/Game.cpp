#include "Game.h"
#include "GameLoop.h"
#include "terrain/Terrain.h"
#include "terrain/Chunk.h"
#include "shaders/Lighting.h"

Game::Game()
    : window(&camera),
    shader("./src/glsl/VertexShader.glsl", "./src/glsl/FragmentShader.glsl"),
    inputManager(window.getWindow(), &camera, &player),
    terrain(shader, 100, 100), // create terrain
    chunk(terrain, glm::vec2(0, 0)), // create a chunk
    guiManager(window.getWindow()),  // initialize GuiManager
    gameLoop(&window, &camera, &player, &inputManager, &shader, &terrain, &chunk, &guiManager) {
    shader.use();

    Lighting sunLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sunLight.setLight(shader);  // set the light properties in the shader
    glEnable(GL_DEPTH_TEST);
}

Game::~Game() {
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Game::run() {
    gameLoop.run();
}

int main() {
    Game game;
    game.run();
    return 0;
}