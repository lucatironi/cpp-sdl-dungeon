#include "game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char *title, int windowWidth, int windowHeight)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        Uint32 flags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN;
        Window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            flags);

        Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);

        IsRunning = true;
    } else {
        IsRunning = false;
    }
}

void Game::Close()
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}

void Game::ProcessInput(float deltaTime)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        IsRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            IsRunning = false;
            break;
        }
    default:
        break;
    }
}

void Game::Update(float deltaTime)
{
}

void Game::Render()
{
    SDL_RenderClear(Renderer);
    SDL_RenderPresent(Renderer);
}