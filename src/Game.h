#pragma once
#include "Window.h"
#include "Shader.h"
#include "Cube.h"
#include "Player.h"
#include "Camera.h"
#include "InputManager.h"
#include "Grid.h"
#include "Terrain.h"
#include "Chunk.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    Window window;
    Shader shader;
    Player player;
    Camera camera;
    InputManager inputManager;
    Terrain terrain;
    Chunk chunk;
};

int main() {
    Game game;
    game.run();
    return 0;
}
