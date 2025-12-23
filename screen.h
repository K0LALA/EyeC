#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define FONT_NOTO_SANS "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf"
#define FONT_SIZE 24

/** ========== Common SDL methods ========== **/
void init();
void finish();
void updateScreen();
void clearRenderingTarget();
void renderOnMainTexture();
void displayMainTexture();
int renderText(const char *text, const int x, const int y);

/** ========== EyeC specific methods ========== **/
void renderDrawRegion(const int wRegion, const int hRegion, const uint8_t drawRegion[][wRegion], const int x, const int y, const int cellDrawSize);

#endif