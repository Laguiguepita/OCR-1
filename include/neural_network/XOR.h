#ifndef XOR_H
#define XOR_H

#include "neural_network.h"

double XOR_front_propagation(Network* network, double inputs[]);
void XOR_back_propagation(Network* network, double expected[]);
void XOR_training(Network* network, double eta, unsigned int epochs, unsigned int batchsize);

#endif
