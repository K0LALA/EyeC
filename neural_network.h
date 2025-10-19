#ifndef NN_H
#define NN_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "constants.h"

// The number of layers, counting the input layer
#define LAYER_COUNT 4

typedef struct Layer Layer;

/// @brief Describes one layer of a NN
struct Layer {
    int size;                   // The number of cells in the layer
    int previousSize;           // The number of cells in the previous layer
    double *cells;              // The values for each cell
    double *biases;             // The biases for each cell
    double **weights;           // The weights for each cell for each connection (from previous layer)
};

// Range: [0;1]
#define ACTIVATION_FUNCTION(val) (1 / (1 + exp(-val)))

#endif
