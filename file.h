#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdint.h>

#include "constants.h"

#define MAX_FILE_COUNT 2

int openFile(FILE** file, const char* fileName);
void closeFiles();
void getNextDigit(FILE* imagesFile, FILE* labelsFile, uint8_t drawRegion[][CELL_WIDTH], uint8_t *label);
uint32_t read32FromFile(FILE* file);
uint8_t read8FromFile(FILE* file);
void readDrawRegion(FILE* file, uint8_t drawRegion[][CELL_WIDTH]);

#endif
