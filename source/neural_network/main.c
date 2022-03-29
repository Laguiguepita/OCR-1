#include "../../include/neural_network/neural_network.h"
#include "../../include/neural_network/save_and_load.h"
#include "../../include/neural_network/XOR.h"
#include <stdio.h>
#include <math.h>

int main(){
	
	
	//unsigned int sizes[] = {2,4,5,1};
	//Network* network = initNetwork(sizes, sizeof(sizes)/sizeof(unsigned int));
	Network* network = loadNetwork("test1");
	//saveNetwork(network, "test1");

	trainning(network, 0.2, 4000);
	//feedforward(network, inputs);
	saveNetwork(network, "test1");
	freeNetwork(network);
	return 0;
}
