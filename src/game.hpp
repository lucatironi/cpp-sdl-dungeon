#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game
{
    public:
        Game();
        ~Game();

        void Init(const char *title, int windowWidth, int windowHeight);
        void Close();

        void ProcessInput(float deltaTime);
        void Update(float deltaTime);
        void Render();

        bool IsRunning;
        bool Keys[1024];
        bool KeysProcessed[1024];

      private:
        int WindowWidth;
        int WindowHeight;
        SDL_Window *Window;
        SDL_Renderer *Renderer;
};

#endif