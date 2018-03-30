#include "game.hpp"

#include <cmath>

const int MapWidth = 24;
const int MapHeight = 24;

int WorldMap[MapWidth][MapHeight] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

double posX = 22, posY = 12;      // x and y start position
double dirX = -1, dirY = 0;       // initial direction vector
double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char *title, int windowWidth, int windowHeight)
{
    this->WindowWidth = windowWidth;
    this->WindowHeight = windowHeight;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        Uint32 flags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_SHOWN;
        this->Window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            flags);

        this->Renderer = SDL_CreateRenderer(this->Window, -1, SDL_RENDERER_ACCELERATED);

        this->IsRunning = true;
    } else {
        this->IsRunning = false;
    }
}

void Game::Close()
{
    SDL_DestroyWindow(this->Window);
    SDL_DestroyRenderer(this->Renderer);
    SDL_Quit();
}

void Game::ProcessInput(float deltaTime)
{
    double oldDirX = dirX;
    double oldPlaneX = planeX;

    double moveSpeed = 0.01;
    double rotateSpeed = 0.01;

    if (this->Keys[SDLK_w])
    {
        if (WorldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
            posX += dirX * moveSpeed;
        if (WorldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
            posY += dirY * moveSpeed;
    }
    if (this->Keys[SDLK_s])
    {
        if (WorldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
            posX -= dirX * moveSpeed;
        if (WorldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
            posY -= dirY * moveSpeed;
    }
    if (this->Keys[SDLK_a])
    {
        dirX = dirX * cos(rotateSpeed) - dirY * sin(rotateSpeed);
        dirY = oldDirX * sin(rotateSpeed) + dirY * cos(rotateSpeed);
        planeX = planeX * cos(rotateSpeed) - planeY * sin(rotateSpeed);
        planeY = oldPlaneX * sin(rotateSpeed) + planeY * cos(rotateSpeed);
    }
    if (this->Keys[SDLK_d])
    {
        dirX = dirX * cos(-rotateSpeed) - dirY * sin(-rotateSpeed);
        dirY = oldDirX * sin(-rotateSpeed) + dirY * cos(-rotateSpeed);
        planeX = planeX * cos(-rotateSpeed) - planeY * sin(-rotateSpeed);
        planeY = oldPlaneX * sin(-rotateSpeed) + planeY * cos(-rotateSpeed);
    }

    if (this->Keys[SDLK_ESCAPE])
    {
        this->IsRunning = false;
        this->KeysProcessed[SDLK_ESCAPE] = true;
    }
}

void Game::Update(float deltaTime)
{
}

void Game::Render()
{
    SDL_SetRenderDrawColor(this->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->Renderer);
    for (int x = 0; x < this->WindowWidth; x++)
    {
        // Calculate ray position and direction
        double cameraX = 2 * x / double(this->WindowWidth) - 1; // x-coordinate in camera space
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // Which box of the map we're in
        int mapX = int(posX);
        int mapY = int(posY);

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = std::abs(1 / rayDirX);
        double deltaDistY = std::abs(1 / rayDirY);
        double perpWallDist;

        // What direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side;    // Was a NS or a EW wall hit?
        
        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (WorldMap[mapX][mapY] > 0)
                hit = 1;
        }
        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(this->WindowHeight / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + this->WindowHeight / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + this->WindowHeight / 2;
        if (drawEnd >= this->WindowHeight)
            drawEnd = this->WindowHeight - 1;

        // Choose wall color
        int colorR, colorG, colorB;
        switch (WorldMap[mapX][mapY])
        {
        case 1:
            colorR = 255;
            colorG = 0;
            colorB = 0;
            break; // red
        case 2:
            colorR = 0;
            colorG = 255;
            colorB = 0;
            break; // green
        case 3:
            colorR = 0;
            colorG = 0;
            colorB = 255;
            break; // blue
        case 4:
            colorR = 255;
            colorG = 255;
            colorB = 255;
            break; // white
        default:
            colorR = 0;
            colorG = 255;
            colorB = 255;
            break; // yellow
        }

        //give x and y sides different brightness
        if (side == 1)
        {
            colorR = colorR / 2;
            colorG = colorG / 2;
            colorB = colorB / 2;
        }

        SDL_SetRenderDrawColor(this->Renderer, 56, 56, 56, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(this->Renderer, x, 0, x, drawStart);
        SDL_SetRenderDrawColor(this->Renderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(this->Renderer, x, drawStart, x, drawEnd);
        SDL_SetRenderDrawColor(this->Renderer, 112, 112, 112, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(this->Renderer, x, drawEnd, x, this->WindowHeight);
    }
    SDL_RenderPresent(this->Renderer);
}