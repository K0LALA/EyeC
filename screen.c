#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "screen.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer;

SDL_Color foregroundColor = {255, 255, 255, 255};
SDL_Color backgroundColor = {0, 0, 0, 255};

SDL_Texture *mainTexture;

/// @brief Initialize window and renderer, open empty window
void init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS, &window, &renderer) != 0)
    {
        printf("SDL_CreateWindowAndRenderer Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetWindowMinimumSize(window, 1024, 768);

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(window, "Octis");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    mainTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!mainTexture)
    {
        printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/// @brief Destroys mainTexuture, renderer, window and terminates SDL
void finish()
{
    SDL_DestroyTexture(mainTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
