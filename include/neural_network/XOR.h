#ifndef XOR_H
#define XOR_H

#include "neural_network.h"

double XOR_front_propagation(Network* network, double inputs[]);
void XOR_trainning(Network* network, double eta, unsigned int epochs);

#endif
