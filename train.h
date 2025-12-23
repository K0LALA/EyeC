#ifndef TRAIN_H
#define TRAIN_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "neural_network.h"

void genRandomDoubles(unsigned int size, double array[size], double min, double max);
void initLayers(NeuralNetwork NN, double min, double max);
void displayLayer(Layer layer);
void displayLayerCells(Layer layer);
void displayLayerBiases(Layer layer);
void displayLayerWeights(Layer layer);
void destroyLayers(NeuralNetwork NN);

#endif
