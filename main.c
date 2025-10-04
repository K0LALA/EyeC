#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "screen.h"


int main(int argc, char **argv)
{
    init();

    uint8_t testDrawRegion[CELL_WIDTH][CELL_WIDTH] = 
    {{0, 0, 75, 0, 0},
    {0, 75, 130, 75, 0},
    {75, 130, 255, 130, 75},
    {0, 75, 130, 75, 0},
    {0, 0, 75, 0, 0}};

    renderOnMainTexture();
    renderDrawRegion(testDrawRegion, 50, 50, 50);
    displayMainTexture();

    SDL_Delay(2000);

    finish();

    return 0;
}