#include <SDL2/SDL.h>

#include "game.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

Game *Dungeon = nullptr;

int main()
{
    Dungeon = new Game();

    Dungeon->Init("Dungeon", WINDOW_WIDTH, WINDOW_HEIGHT);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (Dungeon->Running())
    {
        float currentFrame = SDL_GetPerformanceCounter();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Dungeon->ProcessInput(deltaTime);
        Dungeon->Update(deltaTime);
        Dungeon->Render();
    }

    Dungeon->Close();

    return 0;
}