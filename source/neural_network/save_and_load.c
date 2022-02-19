#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "../../include/neural_network/save_and_load.h"

void saveNetwork(Network network, char name[]){
	FILE* file = NULL;
	char destination[] = "saves/";
	strcat(destination, name);
	file = fopen(destination, "w");

	if(file == NULL){
    		errx(1, "something goes wrong");
	}
	for(unsigned int i = 0; i < network.nb_layers;i++){
		fprintf(file, "%i-", network.layers[i].nb_neurons);
	}
	fprintf(file, "\n");
	for(unsigned int i = 1; i < network.nb_layers; i++){
		fprintf(file, "new layer\n");
		for(unsigned int j = 0; j < network.layers[i].nb_neurons; j++){
			fprintf(file, "%f\n", network.layers[i].neurons[j].bias);
			for(unsigned int l = 0;
				       	l < network.layers[i].neurons[j].nb_weights; l++){
				fprintf(file ,"%f /", network.layers[i].neurons[j].weights[l]);
			}
			fprintf(file, "\n");
		}
		fprintf(file, "\n");
	}


	fclose(file);
}
