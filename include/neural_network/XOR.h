#ifndef XOR_H
#define XOR_H

#include "neural_network.h"

double log_loss(double results[], double expected_results[], size_t length);
double feedforward(Network* network, double inputs[]);

#endif
