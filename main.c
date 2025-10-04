#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "screen.h"


int main(int argc, char **argv)
{
    init();

    SDL_Delay(2000);

    finish();

    return 0;
}