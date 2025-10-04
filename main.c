#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "screen.h"

const char* IMAGES_FILE = "train-images-idx3-ubyte";
const char* LABELS_FILE = "train-labels-idx1-ubyte";
const _Bool training = 1;

int count;
int cols;
int rows;

uint32_t read32FromFile(FILE* file)
{
    uint32_t number = 0;
    uint32_t multiplier = 16777216;
    for (int i = 0; i < 4; i++)
    {
        number += fgetc(file) * multiplier;
        multiplier /= 256;
    }
    return number;
}

/// @brief Reads the file and parses data to `drawRegion`
/// @param file The images file to read from
/// @param drawRegion A pointer to the 2D array to place content in
void readDrawRegion(FILE* file, uint8_t drawRegion[][CELL_WIDTH])
{
    for (int y = 0; y < CELL_WIDTH; y++)
    {
        for (int x = 0; x < CELL_WIDTH; x++)
        {
            drawRegion[y][x] = fgetc(file);
        }
    }
}

int main(int argc, char **argv)
{
    FILE* imagesFile = NULL;
    FILE* labelsFile = NULL;

    imagesFile = fopen(IMAGES_FILE, "r");
    if (imagesFile == NULL)
    {
        puts("Error when trying to open images file");
        return EXIT_FAILURE;
    }

    
    // Test magic number (32-bit)
    uint32_t magic = read32FromFile(imagesFile);

    if (magic != 2051)
    {
        printf("Magic number is not right: %d", magic);
        fclose(imagesFile);
        return EXIT_FAILURE;
    }

    count = read32FromFile(imagesFile);
    rows = read32FromFile(imagesFile);
    cols = read32FromFile(imagesFile);
    printf("%d %d %d\n", count, rows, cols);

    
    labelsFile = fopen(LABELS_FILE, "r");
    if (labelsFile == NULL)
    {
        puts("Error when trying to open labels file");
        fclose(imagesFile);
        return EXIT_FAILURE;
    }
    
    init();

    uint8_t testDrawRegion[CELL_WIDTH][CELL_WIDTH];
    readDrawRegion(imagesFile, testDrawRegion);

    renderOnMainTexture();
    renderDrawRegion(testDrawRegion, 50, 50, 10);
    displayMainTexture();

    SDL_Delay(2000);

    readDrawRegion(imagesFile, testDrawRegion);

    renderOnMainTexture();
    renderDrawRegion(testDrawRegion, 50, 50, 10);
    displayMainTexture();

    SDL_Delay(2000);

    finish();

    fclose(imagesFile);
    fclose(labelsFile);

    return 0;
}