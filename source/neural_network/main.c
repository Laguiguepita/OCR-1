#include "../../include/neural_network/neural_network.h"
#include "../../include/neural_network/save_and_load.h"
#include "../../include/neural_network/XOR.h"
#include <stdio.h>

int main(){
	unsigned int sizes[] = {2,2,1};
	Network* network = initNetwork(sizes, sizeof(sizes)/sizeof(unsigned int));
	//Network* network = loadNetwork("test");


	double inputsList[4][2] = {{0, 1}, {1, 1}, {0, 0}, {1, 0}};
	double expected_resultsList[] = {1, 0, 0, 1};
	double resultsList[4];
	for(size_t i = 0; i < 4; i++){
		printf("the inputs are: %f and %f\n",
			       	inputsList[i][0], inputsList[i][1]);
		resultsList[i] = feedforward(network, inputsList[i]);
	}
	double x = log_loss(resultsList, expected_resultsList, 4);
	printf("%f\n", x);
	//feedforward(network, inputs);
	//saveNetwork(network, "test");
	freeNetwork(network);
	return 0;
}
