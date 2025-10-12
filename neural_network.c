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

    layer->nextLayer = NULL;
}
