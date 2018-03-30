#include <SDL2/SDL.h>

#include "game.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

Game *Dungeon = nullptr;

void capture_input();

int main()
{
    Dungeon = new Game();

    Dungeon->Init("Dungeon", WINDOW_WIDTH, WINDOW_HEIGHT);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (Dungeon->IsRunning)
    {
        float currentFrame = SDL_GetPerformanceCounter();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        capture_input();

        Dungeon->ProcessInput(deltaTime);
        Dungeon->Update(deltaTime);
        Dungeon->Render();
    }

    Dungeon->Close();

    return 0;
}

void capture_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        Dungeon->IsRunning = false;
        break;
    case SDL_KEYDOWN:
        Dungeon->Keys[event.key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        Dungeon->Keys[event.key.keysym.sym] = false;
        Dungeon->KeysProcessed[event.key.keysym.sym] = false;
        break;
    }
}