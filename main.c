#include "main.h"

const char* IMAGES_FILE = IMAGES_FILE_PATH;
const char* LABELS_FILE = LABELS_FILE_PATH;
const bool training = true;

SDL_Event event;

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

    uint32_t currentDigit = 0;
    char currentDigitText[18] = "\0";
    sprintf(currentDigitText, INDEX_PLACEHOLDER, currentDigit);

    uint8_t drawRegion[CELL_WIDTH][CELL_WIDTH];
    uint8_t label;
    getNextDigit(imagesFile, labelsFile, drawRegion, &label);
    char labelText[11] = "\0";
    sprintf(labelText, DIGIT_PLACEHOLDER, label);

    bool stopping = false;
    bool render = true;
    while (!stopping)
    {
        if (render)
        {
            sprintf(currentDigitText, INDEX_PLACEHOLDER, currentDigit);
            sprintf(labelText, DIGIT_PLACEHOLDER, label);

            renderOnMainTexture();
            clearRenderingTarget();
            renderDrawRegion(drawRegion, 50, 50, 10);
            renderText(labelText, 50, 340);
            renderText(currentDigitText, 50, 370);
            displayMainTexture();
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                stopping = true;
                break;

            case SDL_KEYDOWN:
                int key = event.key.keysym.sym;
                if (key == SDLK_ESCAPE)
                {
                    stopping = true;
                }
                else if (key == SDLK_RIGHT)
                {
                    // Read next digit
                    currentDigit++;
                    if (currentDigit >= count)
                    {
                        currentDigit = 0;
                        fseek(imagesFile, 16, SEEK_SET);
                        fseek(labelsFile, 8, SEEK_SET);
                    }
                    getNextDigit(imagesFile, labelsFile, drawRegion, &label);
                    render = true;
                }
                else if (key == SDLK_LEFT)
                {
                    // Read last digit
                    if (currentDigit == 0)
                    {
                        currentDigit = count;
                        fseek(imagesFile, -1 * rows * cols, SEEK_END);
                        fseek(labelsFile, -1, SEEK_END);
                    }
                    currentDigit--;
                    // Move cursor back
                    fseek(imagesFile, -2 * rows * cols, SEEK_CUR);
                    fseek(labelsFile, -2, SEEK_CUR);
                    getNextDigit(imagesFile, labelsFile, drawRegion, &label);
                    render = true;
                }
                break;
            }
        }
    }

    finish();

    closeFiles();

    return 0;
}