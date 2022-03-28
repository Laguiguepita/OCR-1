#include "../../include/neural_network/neural_network.h"
#include "../../include/neural_network/save_and_load.h"
#include "../../include/neural_network/XOR.h"
#include <stdio.h>
#include <math.h>

int main(){
	
	
	unsigned int sizes[] = {2,2,1};
	Network* network = initNetwork(sizes, sizeof(sizes)/sizeof(unsigned int));
	//Network* network = loadNetwork("test");
	saveNetwork(network, "test1");

	//trainning(network, 1.0, 1000);
	//feedforward(network, inputs);
	//saveNetwork(network, "test2");
	freeNetwork(network);
	return 0;
}
