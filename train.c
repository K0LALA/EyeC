#include "train.h"

const unsigned int LAYER_SIZES[LAYER_COUNT] = {CELL_WIDTH * CELL_WIDTH, 500, 1000, 10};


int main(int argc, char **argv)
{
    // Array of pointer to layers
    // We do not count the first layer here since it does not have previousSize, nor weights, nor biases, nor activation function
    // TODO: Decide whether or not to create a struct for the NN containing a layer array, the input layer, and the size.
    Layer NN[LAYER_COUNT - 1];

    initLayers(NN, -1.0, 1.0);
    displayLayer(NN[0]);

    destroyLayers(NN);

    return 0;
}

/// @brief Generates a list of `double` in [min;max]
/// @param size The size of the array
/// @param array The array
/// @param min The min bound
/// @param max The max bound
void genRandomDoubles(unsigned int size, double array[size], double min, double max)
{
    double range = max - min;
    double ratio = RAND_MAX / range;
    for (int i = 0; i < size; i++)
    {
        array[i] = min + (rand() / ratio);
    }
}

/// @brief Resets the NN with random values between min and max
/// @brief Usually called once to get a start then remove call to train using these random values
/// @param NN The array of layers without the input layer
/// @param min The minimum bound
/// @param max The maximum bound
void initLayers(Layer NN[LAYER_COUNT - 1], double min, double max)
{
    srand(time(NULL));
    for (int i = 0; i < LAYER_COUNT - 1; i++)
    {
        unsigned int size = LAYER_SIZES[i + 1];
        NN[i].size = size;
        unsigned int previousSize = LAYER_SIZES[i];
        NN[i].previousSize = previousSize;

        double *cells = (double*)malloc(sizeof(double) * size);
        memset(cells, 0, size);
        NN[i].cells = cells;

        double *biases = (double*)malloc(sizeof(double) * size);
        genRandomDoubles(size, biases, -1.0, 1.0);
        NN[i].biases = biases;

        // Allocate the array of pointers
        double** weights = (double**)malloc(sizeof(double*) * size);
        for (int j = 0; j < size; j++)
        {
            // Allocate the array of doubles
            double* connectionWeights = (double*)malloc(sizeof(double) * previousSize);
            genRandomDoubles(previousSize, connectionWeights, -1.0, 1.0);
            weights[j] = connectionWeights;
        }
        NN[i].weights = weights;
    }
}

void displayLayer(Layer layer)
{
    puts("\nCells: ");
    displayLayerCells(layer);
    puts("\nBiases: ");
    displayLayerBiases(layer);
    puts("\nWeights: ");
    displayLayerWeights(layer);
}

void displayLayerCells(Layer layer)
{
    for (int i = 0; i < layer.size; i++)
    {
        printf("%f ", layer.cells[i]);
    }
}

void displayLayerBiases(Layer layer)
{
    for (int i = 0; i < layer.size; i++)
    {
        printf("%f ", layer.biases[i]);
    }
}

void displayLayerWeights(Layer layer)
{
    for (int i = 0; i < layer.size; i++)
    {
        for (int j = 0; j < layer.previousSize; j++)
        {
            printf("%f ", layer.weights[i][j]);
        }
        printf("\n");
    }
}

void destroyLayers(Layer NN[LAYER_COUNT - 1])
{
    for (int i = 0; i < LAYER_COUNT - 1; i++)
    {
        free(NN[i].cells);
        free(NN[i].biases);
        free(NN[i].weights);
    }
}
