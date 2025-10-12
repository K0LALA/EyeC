#ifndef NN_H
#define NN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Layer Layer;

/// @brief Describes one layer of a NN
struct Layer {
    int size;                   // The number of cells in the layer
    int previousSize;           // The number of cells in the previous layer
    double *cells;              // The values for each cell
    double *biases;             // The biases for each cell
    double **weights;           // The weights for each cell for each connection
    // TODO: Change to previousLayer?
    // TODO: Makes init faster because no backtracking for pointers or previousSize
    struct Layer* nextLayer;    // A pointer to the next layer
};

#endif
