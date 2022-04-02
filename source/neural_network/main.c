#include "../../include/neural_network/neural_network.h"
#include "../../include/neural_network/save_and_load.h"
#include "../../include/neural_network/XOR.h"
#include "../../include/neural_network/data_set.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv){
	Network* network;
	for(int i = 1; i < argc; i++){
		if(strcmp("-g", argv[i]) == 0){
			size_t size = 1;
			for(size_t j = 0; j < strlen(argv[i+1]); j++){
				if(argv[i+1][j] == '-'){
					size++;
				}
			}
			unsigned int* sizes;
			sizes = malloc(sizeof(unsigned int) * size);
			if(sizes == NULL){
				errx(1, "Not enough memory!");
			}
			char* endPtr;
			for(size_t j = 0; j < size; j++){
				sizes[j] = strtol(argv[i+1], &endPtr, 10);
				argv[i+1] = endPtr + 1;
			}
			network = initNetwork(sizes, size);
			i++;
		}
		if(strcmp("-l", argv[i]) == 0){
			network = loadNetwork(argv[i+1]);
			i++;
		}
		if(strcmp("-t", argv[i]) == 0){
			XOR_trainning(network, 0.3, 100000);
		}
		if(strcmp("-s", argv[i]) == 0){
			saveNetwork(network, argv[i+1]);
			i++;
		}
		if(strcmp("-d", argv[i]) == 0){
			load_image();
		}
	}
	if(network != NULL){
		freeNetwork(network);
	}
	//load_image();
	//load_label();

	
	//unsigned int sizes[] = {2,8,6,4,1};
	//Network* network = initNetwork(sizes, sizeof(sizes)/sizeof(unsigned int));
	//Network* network = loadNetwork("test1");
	//saveNetwork(network, "test1");
	

	//XOR_trainning(network, 0.3, 100000);
	//feedforward(network, inputs);
	//saveNetwork(network, "test1");
	//freeNetwork(network);
	return 0;
}
