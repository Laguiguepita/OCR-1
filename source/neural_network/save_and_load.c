#include "../../include/neural_network/save_and_load.h"
#include <math.h>

#define MAX_LENGTH 10000

void saveNetwork(Network* network, char path[]){
	// try to open the file
	FILE* file = NULL;
	file = fopen(path, "w+");
	if(file == NULL){
    		errx(1, "failed to open the file");
	}

	// write the format of the network
	fprintf(file, "%i", network->layers[0]->nb_neurons);
	for(unsigned int i = 1; i < network->nb_layers; i++){
		fprintf(file, "-%i", network->layers[i]->nb_neurons);
	}
	fprintf(file, "\n");

	// write all informations
	for(unsigned int i = 1; i < network->nb_layers; i++){
		fprintf(file, "new layer\n");
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			fprintf(file, "%f|", network->layers[i]->neurons[j]->bias);
			fprintf(file, "%f", network->layers[i]->neurons[j]->weights[0]);
			for(unsigned int l = 1;
				       	l < network->layers[i]->neurons[j]->nb_weights; l++){
				fprintf(file ,"/%f", network->layers[i]->neurons[j]->weights[l]);
			}
			fprintf(file, "\n");
		}
	}

	// close the file
	fclose(file);
}



Network* loadNetwork(char path[]){
	// try to open the file
	FILE* file = NULL;
	file = fopen(path, "r");
	if(file == NULL){
		errx(1, "failed to open the file");
	}

	// count the number of layers in the network
	char text[MAX_LENGTH] = "";
	fgets(text, MAX_LENGTH, file);
	size_t size = 1;
	for(size_t i = 0; i < strlen(text); i++){
		if (text[i] == '-'){
			size++;
		}
	}
	
	// try to collect the format of the network
	unsigned int* sizes;
	sizes = malloc(sizeof(unsigned int) * size);
	if(sizes == NULL){
		errx(1, "Not enough memory!");
	}
	char* text2 = text;
	char* endPtr;
	for(size_t i = 0; i < size; i++){
		sizes[i] = strtol(text2, &endPtr, 10);
		text2 = endPtr + 1;
	}

	// create the network
	Network* network = newNetwork(sizes, size);

	free(sizes);

	// load all informations in the network
	unsigned int layerIndex = 0;
	unsigned int neuronIndex = 0;
	unsigned int weightIndex = 0;

	while(fgets(text, MAX_LENGTH, file)){	
		if(strcmp(text, "\n") == 0){
			continue;
		}
		else if(strcmp(text, "new layer\n") == 0){
			layerIndex++;
			neuronIndex = 0;
			weightIndex = 0;
		}
		else{
			text2 = text;
			network->layers[layerIndex]->neurons[neuronIndex]->bias =
				strtod(text2, &endPtr);
			while(strcmp(endPtr, "\n") != 0){
				text2 = endPtr + 1;
				network->layers[layerIndex]->neurons[neuronIndex]->weights[weightIndex] =
					strtod(text2, &endPtr);
				weightIndex++;
			}
			weightIndex = 0;
			neuronIndex++;
		}
	
	}
	// closing the file
	fclose(file);

	return network;
}
