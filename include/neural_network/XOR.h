#ifndef XOR_H
#define XOR_H

#include "neural_network.h"

double feedforward(Network* network, double inputs[]);
void trainning(Network* network, double eta, unsigned int epochs);

#endif
