#include "train.h"

const unsigned int LAYER_SIZES[LAYER_COUNT] = {CELL_WIDTH * CELL_WIDTH, 500, 256, 10};

int main(int argc, char **argv)
{
    NeuralNetwork NN = {LAYER_COUNT, (int*) LAYER_SIZES, NULL};
    // Array of pointer to layers
    // We do not count the first layer here since it does not have previousSize, nor weights, nor biases, nor activation function
    Layer layers[LAYER_COUNT - 1];
    NN.layers = layers;

    initLayers(NN, -1.0, 1.0);
    displayLayer(NN.layers[2]);

    storeNN(NN, "neural_network-sigmoid.bin");

    destroyLayers(NN);

    loadNN(NN, "neural_network-sigmoid.bin");

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
/// @param NN The neural network
/// @param min The minimum bound
/// @param max The maximum bound
void initLayers(NeuralNetwork NN, double min, double max)
{
    srand(time(NULL));
    for (int i = 0; i < NN.layerCount - 1; i++)
    {
        unsigned int size = LAYER_SIZES[i + 1];
        NN.layers[i].size = size;
        unsigned int previousSize = LAYER_SIZES[i];
        NN.layers[i].previousSize = previousSize;

        double *cells = (double*)malloc(sizeof(double) * size);
        memset(cells, 0, size);
        NN.layers[i].cells = cells;

        double *biases = (double*)malloc(sizeof(double) * size);
        genRandomDoubles(size, biases, -1.0, 1.0);
        NN.layers[i].biases = biases;

        // Allocate the array of pointers
        double** weights = (double**)malloc(sizeof(double*) * size);
        for (int j = 0; j < size; j++)
        {
            // Allocate the array of doubles
            double* connectionWeights = (double*)malloc(sizeof(double) * previousSize);
            genRandomDoubles(previousSize, connectionWeights, -1.0, 1.0);
            weights[j] = connectionWeights;
        }
        NN.layers[i].weights = weights;
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

/// @brief Frees dynamically allocated arrays from the neural network
/// @param NN The neural network
void destroyLayers(NeuralNetwork NN)
{
    for (int i = 0; i < NN.layerCount - 1; i++)
    {
        free(NN.layers[i].cells);
        free(NN.layers[i].biases);
        free(NN.layers[i].weights);
    }
}
