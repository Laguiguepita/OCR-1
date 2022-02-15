#include "../../include/neural_network/neural_network.h"

int main(){
	unsigned int sizes[] = {3,4,10};

	Network network = newNetwork(sizes, 3);
	initNetwork(network);
	double inputs[3] = {3, 2, 7};
	feedforward(network, inputs);
	freeNetwork(network);
	return 0;


}
