#include <stdio.h>
#include <stdint.h>

#include "file.h"

FILE *openedFiles[MAX_FILE_COUNT];
int openedFilesCount = 0;

/// @brief Opens the file
/// @param file The file variable
/// @param fileName The path to the file
/// @return 0 on success, 1 on failure
int openFile(FILE** file, const char* fileName)
{
    *file = fopen(fileName, "r");
    if (*file == NULL)
    {
        printf("Couldn't open %s\n", fileName);
        return 1;
    }

    if (openedFilesCount == MAX_FILE_COUNT)
    {
        puts("There are two many files opened, this one will need to be closed manually.\n");
    }
    else {
        openedFiles[openedFilesCount] = *file;
        openedFilesCount++;
    }

    return 0;
}

/// @brief Closes all opened files
void closeFiles()
{
    for (int i = 0; i < openedFilesCount; i++)
    {
        fclose(openedFiles[i]);
        openedFiles[i] = NULL;
    }
}

void getNextDigit(FILE* imagesFile, FILE* labelsFile, uint8_t drawRegion[][CELL_WIDTH], uint8_t *label)
{
    readDrawRegion(imagesFile, drawRegion);
    *label = read8FromFile(labelsFile);
}

uint8_t read8FromFile(FILE* file)
{
    uint8_t number = fgetc(file);
    return number;
}

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
