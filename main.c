#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "main.h"
#include "file.h"
#include "screen.h"

const char* IMAGES_FILE = "train-images-idx3-ubyte";
const char* LABELS_FILE = "train-labels-idx1-ubyte";
const _Bool training = 1;

int main(int argc, char **argv)
{
    FILE* imagesFile = NULL;
    FILE* labelsFile = NULL;

    if (openFile(&imagesFile, IMAGES_FILE))
    {
        return EXIT_FAILURE;
    }
    if (openFile(&labelsFile, LABELS_FILE))
    {
        closeFiles();
        return EXIT_FAILURE;
    }

    // Test magic number (32-bit)
    uint32_t magic = read32FromFile(imagesFile);

    if (magic != 2051)
    {
        printf("Magic number is not right: %u", magic);
        closeFiles();
        return EXIT_FAILURE;
    }

    uint32_t count;
    int cols;
    int rows;

    count = read32FromFile(imagesFile);
    rows = read32FromFile(imagesFile);
    cols = read32FromFile(imagesFile);
    printf("%u %u %u\n", count, rows, cols);

    uint32_t labelsMagic = read32FromFile(labelsFile);
    if (labelsMagic != 2049)
    {
        printf("Magic number is not right: %u", labelsMagic);
        closeFiles();
    }

    uint32_t labelsCount = read32FromFile(labelsFile);
    if (count != labelsCount)
    {
        printf("Counts do not match: %d\n", labelsCount);
        closeFiles();
        return EXIT_FAILURE;
    }
    
    init();

    uint8_t testDrawRegion[CELL_WIDTH][CELL_WIDTH];
    readDrawRegion(imagesFile, testDrawRegion);
    uint8_t label = read8FromFile(labelsFile);
    char labelText[11] = "\0";
    sprintf(labelText, "Digit: %d", label);

    renderOnMainTexture();
    renderDrawRegion(testDrawRegion, 50, 50, 10);
    renderText(labelText, 50, 340);
    displayMainTexture();

    SDL_Delay(2000);

    readDrawRegion(imagesFile, testDrawRegion);
    label = read8FromFile(labelsFile);
    sprintf(labelText, "Digit: %d", label);

    renderOnMainTexture();
    clearRenderingTarget();
    renderDrawRegion(testDrawRegion, 50, 50, 10);
    renderText(labelText, 50, 340);
    displayMainTexture();

    SDL_Delay(2000);

    finish();

    closeFiles();

    return 0;
}