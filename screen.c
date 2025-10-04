#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "screen.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer;

SDL_Color foregroundColor = {255, 255, 255, 255};
SDL_Color backgroundColor = {0, 0, 0, 255};

SDL_Texture *mainTexture;


/** ========== Common SDL methods ========== **/

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

void updateScreen()
{
    SDL_RenderPresent(renderer);
}

/// @brief Clears the screen
void clearScreen()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

/// @brief Renders to intermediate texture, in the stack
void renderOnMainTexture()
{
    if (SDL_SetRenderTarget(renderer, mainTexture) < 0)
    {
        printf("SDL_SetRenderTarget Error: %s\n", SDL_GetError());
    }
}

/// @brief Updates what's on the screen from the intermediate texture
void displayMainTexture()
{
    // Set render target to screen
    if (SDL_SetRenderTarget(renderer, NULL) < 0)
    {
        printf("SDL_SetRenderTarget2 Error: %s\n", SDL_GetError());
        return;
    }
    // Render copy from texture to screen
    SDL_RenderCopy(renderer, mainTexture, NULL, NULL);

    // Render present
    SDL_RenderPresent(renderer);
}

/** ========== EyeC specific methods ========== **/

/// @brief Draws the `drawRegion` at the defined position (top-left), each pixel of the region has the size defined by `cellSize`
/// @param drawRegion A 2D Square array with integers ranging 0-255, O is black, 1 is white
/// @param x Abscissa (left)
/// @param y Ordinate (top)
/// @param cellWidth Width of one pixel for the region
void renderDrawRegion(const uint8_t drawRegion[][CELL_WIDTH], const int x, const int y, const int cellDrawSize)
{
    // Outline, the inside doesn't need to be erased, if some parts aren't covered, it's the user's fault
    SDL_Rect outline = {x - 3, y - 3, cellDrawSize * CELL_WIDTH + 6, cellDrawSize * CELL_WIDTH + 6};
    SDL_SetRenderDrawColor(renderer, foregroundColor.r, foregroundColor.g, foregroundColor.b, foregroundColor.a);
    SDL_RenderFillRect(renderer, &outline);

    // Content
    int currentX = x;
    int currentY = y;
    for (int i = 0; i < CELL_WIDTH; i++)
    {
        currentX = x;
        for (int j = 0; j < CELL_WIDTH; j++)
        {
            uint8_t pixelColor = drawRegion[i][j];
            SDL_Rect cellRect = {currentX, currentY, cellDrawSize, cellDrawSize};
            SDL_SetRenderDrawColor(renderer, pixelColor, pixelColor, pixelColor, 255);
            SDL_RenderFillRect(renderer, &cellRect);
            currentX += cellDrawSize;
        }
        currentY += cellDrawSize;
    }
}
