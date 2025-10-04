#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

// TMP, based on training and test sets
#define CELL_WIDTH 5

/** ========== Common SDL methods ========== **/
void init();
void finish();
void updateScreen();
void clearScreen();
void renderOnMainTexture();
void displayMainTexture();

/** ========== EyeC specific methods ========== **/
void renderDrawRegion(const uint8_t drawRegion[][CELL_WIDTH], const int x, const int y, const int cellDrawSize);

#endif