#include "../../include/neural_network/neural_network.h"
#include "../../include/neural_network/save_and_load.h"
#include <stdio.h>

int main(){
//	unsigned int sizes[] = {3,4,10};
//	Network* network = newNetwork(sizes, 3);
//	initNetwork(network);

	Network* network = loadNetwork("test");
	printf("%u", network->nb_layers);
	double inputs[3] = {3, 2, 7};
	feedforward(network, inputs);
	saveNetwork(network, "test1");
	freeNetwork(network);
	return 0;


}
