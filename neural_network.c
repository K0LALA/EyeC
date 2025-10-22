/*
* This file contains methods used to manipulate the Neural Network, abbreviated NN in this file
*/
#include "neural_network.h"

/// @brief Initializes a layer with `size` cells with value 0
/// @param layer The layer to initialize
/// @param size The number of cells
/// @param previousSize The number of cells for the previous layer
/// @param biases An array of biases for each cell
/// @param weights A 2D array containing weights for each link (each cell then each connection to that cell)
void initLayer(Layer *layer, int size, int previousSize, double biases[], double weights[][previousSize])
{    
    layer->size = size;
    layer->previousSize = previousSize;
    layer->biases = biases;
    
    double cells[size];
    layer->weights = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++)
    {
        cells[i] = 0;
        layer->weights[i] = weights[i];
    }
    layer->cells = cells;
}

/// @brief Calculates the value for each cell of `layer` using `previousLayer`
/// @param layer A ponter to the layer to calculate
/// @param previousLayer The previous layer to use for calculation, not changed
void calculateLayer(Layer *layer, Layer *previousLayer)
{
    for (int i = 0; i < layer->size; i++)
    {
        // We reset the cell and apply the bias
        double weightedSum = 0;
        // We connect to every previous cell
        for (int j = 0; j < previousLayer->size; j++)
        {
            weightedSum += previousLayer->cells[j] * layer->weights[i][j];
        }
        layer->cells[i] = ACTIVATION_FUNCTION(weightedSum + layer->biases[i]);
    }
}

/// @brief Maps the input values from [0;255] to [-1;1]
/// @param inputLayer The input layer to place values in
/// @param values The values from the images in the [0;255] range
void mapInputLayer(Layer *inputLayer, uint8_t values[inputLayer->size])
{
    for (int i = 0; i < inputLayer->size; i++)
    {
        inputLayer->cells[i] = (values[i] / 127.5f) - 1;
    }
}

/// Stores the Neural Network in a file.
///
/// The file is written using the following format (inspired by the IDX format):
/// - The first 4 bytes is the magic number, composed by two 0s first.
/// - Then, the type of data (refer to IDX format for more info), here the type is double so 0xOE.
/// - Finally, the number of layers in the Neural Network, not counting the input layer.
/// 
/// After, for each layer of the NN its size is written as a 16-bit integer.
/// Here, the input layer is counted since we need to know its size
/// 
/// Finally the biases, with `length=layerSize`, are written, followed by the weights, with `length=layerSize*previousLayerSize`.
/// @param NN The neural network
/// @param fileName The name of the file to store the file in, content gets overwritten
void storeNN(NeuralNetwork NN, char* fileName)
{
    FILE* file = NULL;
    // Not needed on Linux, but on other OS, useful to make distinction
    file = fopen(fileName, "wb");
    if (file == NULL)
    {
        printf("Couldn't open file: %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    char* buffer = (char*)malloc(sizeof(uint32_t));

    // Magic number, 3587 here
    uint32_t magic = 0x0E * 256 + LAYER_COUNT - 1;    
    memcpy(buffer, &magic, sizeof(uint32_t));
    fwrite(buffer, sizeof(buffer), 1, file);

    // NN sizes
    buffer = (char*)realloc(buffer, LAYER_COUNT * sizeof(uint16_t));
    uint16_t inputLayerSize = NN.layers[0].previousSize;
    memcpy(buffer, &inputLayerSize, sizeof(uint16_t));

    for (int i = 0; i < NN.layerCount - 1; i++)
    {
        uint16_t layerSize = NN.layers[i].size;
        memcpy(buffer + (i + 1) * sizeof(uint16_t), &layerSize, sizeof(uint16_t));
    }
    fwrite(buffer, sizeof(buffer), 1, file);
    free(buffer);
    
    // NN content
    for (int i = 0; i < NN.layerCount - 1; i++)
    {
        size_t size = sizeof(double) * NN.layers[i].size;
        char* biasesBuffer = (char*)malloc(size);
        if (biasesBuffer == NULL)
        {
            puts("Couldn't allocate memory for biasesBuffer");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        memcpy(biasesBuffer, NN.layers[i].biases, size);
        fwrite(biasesBuffer, size, 1, file);
        free(biasesBuffer);

        // Weights
        for (int j = 0; j < NN.layers[i].size; j++)
        {
            size_t weightSize = sizeof(double) * NN.layers[i].previousSize;
            char* weightsBuffer = (char*)malloc(weightSize);
            if (weightsBuffer == NULL)
            {
                puts("Couldn't allocate memory for weightsBuffer");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            memcpy(weightsBuffer, NN.layers[i].weights[j], weightSize);
            fwrite(weightsBuffer, weightSize, 1, file);
            free(weightsBuffer);
        }
    }
   
    fclose(file);
}

/// @brief Loads the content of the file in the NN
/// @param NN The neural network
/// @param fileName The name of the file to read
void loadNN(NeuralNetwork NN, char* fileName)
{
    FILE* file = NULL;
    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        printf("Couldn't open file: %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    uint32_t magic;
    char* buffer = (char*)malloc(sizeof(uint32_t) + 1);
    fgets(buffer, sizeof(uint32_t), file);
    memcpy(&magic, buffer, sizeof(uint32_t));
    printf("Magic: %d\n", magic);

    free(buffer);
    fclose(file);
}

