#pragma once
#include "Window.h"
#include "Shader.h"
#include "Cube.h"
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
    Camera camera;
    InputManager inputManager;
    //Grid grid;
    //Cube cube;
    Terrain terrain;
    Chunk chunk;
};

int main() {
    Game game;
    game.run();
    return 0;
}
