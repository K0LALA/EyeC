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


