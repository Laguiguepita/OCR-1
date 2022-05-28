#ifndef SAVE_AND_LOAD_H
#define SAVE_AND_LOAD_H

#include "neural_network.h"

void saveNetwork(Network* network, char path[]);

Network* loadNetwork(char path[]);

#endif
