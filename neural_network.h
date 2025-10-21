#ifndef NN_H
#define NN_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "constants.h"

// The number of layers, counting the input layer
#define LAYER_COUNT 4

// Range: [0;1]
#define ACTIVATION_FUNCTION(val) (1 / (1 + exp(-val)))


typedef struct Layer Layer;
/// @brief Describes one layer of a NN
struct Layer {
    int size;                   // The number of cells in the layer
    int previousSize;           // The number of cells in the previous layer
    double *cells;              // The values for each cell
    double *biases;             // The biases for each cell
    double **weights;           // The weights for each cell for each connection (from previous layer)
};

void initLayer(Layer *layer, int size, int previousSize, double biases[], double weights[][previousSize]);
void calculateLayer(Layer *layer, Layer *previousLayer);
void mapInputLayer(Layer *inputLayer, uint8_t values[inputLayer->size]);

void storeNN(Layer NN[LAYER_COUNT - 1], char* fileName);
void loadNN(Layer NN[LAYER_COUNT - 1], char* fileName);


#endif
