#ifndef SAVE_AND_LOAD_H
#define SAVE_AND_LOAD_H

#include "neural_network.h"

void saveNetwork(Network* network, char name[]);

Network* loadNetwork(char name[]);

#endif
