#include <math.h>
#include <stdio.h>
#include <err.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "neural_network.h"

Neuron newNeuron(unsigned int nb_weights){
	Neuron neuron = {
		.nb_weights = nb_weights,
		.bias = 0,
		.activation = 0,
		.weights = NULL 
	};
	neuron.weights = malloc(sizeof(double) * nb_weights);
	if(neuron.weights == NULL){
		errx(1, "something goes wrong");
	}
	return neuron;
}


Layer newLayer(unsigned int size, unsigned int previous_layer_size){
	Layer layer = {
		.nb_neurons = size,
		.neurons = NULL
	};
	
	layer.neurons = malloc(sizeof(Neuron) * size);

	/* create neurons for layer */
	for(unsigned int i = 0; i < size; i++){
		layer.neurons[i] = newNeuron(previous_layer_size);
	}
	
	return layer;
}

Network newNetwork(unsigned int sizes[], unsigned int nb_layers){
	Network network = {
		.nb_layers = nb_layers,
		.layers = NULL
	};
	
	// checking if network has a good format
	if(nb_layers < 3){
		errx(1, "Bad neural network format");
	}
	for(unsigned int i = 0; i < nb_layers; i++){
		if (sizes[i] == 0){
			errx(1, "Bad neural network format");
		}
	}
	network.layers = malloc(sizeof(Layer) * nb_layers);
	// create layers for network
	network.layers[0] = newLayer(sizes[0], 0);
	for(unsigned int i = 1; i < nb_layers; i++){
		network.layers[i] = newLayer(sizes[i], sizes[i - 1]);
	}
	
	return network;
}



void initNetwork(Network network){
	srand(time(NULL));
	for(unsigned int i = 1; i < network.nb_layers; i++){
		for(unsigned int j = 0; j < network.layers[i].nb_neurons; j++){
			for(unsigned int l = 0;
			l < network.layers[i].neurons[j].nb_weights; l++){
				network.layers[i].neurons[j].weights[l] =
				 rand() % 10;
			}
			network.layers[i].neurons[j].bias =
			 rand() % 10;
		}
	}
}


void freeNetwork(Network network){
	for(unsigned int i = 0; i < network.nb_layers; i++){
		for(unsigned int j = 0; j < network.layers[i].nb_neurons; j++){
			free(network.layers[i].neurons[j].weights);
		}
		free(network.layers[i].neurons);
	}
	free(network.layers);
}


void feedforward(Network network, double inputs[]){
	for(unsigned int i = 0; i < network.layers[0].nb_neurons; i++){
	network.layers[0].neurons[i].activation = inputs[i];
	}
	double sum = 0;
	// the loop don't go into the first layer and the last layer
	for(unsigned int i = 1; i < network.nb_layers - 1; i++){
		for(unsigned int j = 0; j < network.layers[i].nb_neurons; j++){
			for(unsigned int l = 0;
			l < network.layers[i].neurons[j].nb_weights; l++){
				/* i.e. sum of activation of the neuron in the previous 
				layer multiply by the weight of the actual neuron */
				sum += network.layers[i-1].neurons[l].activation *
				network.layers[i].neurons[j].weights[l];
			}
			// add the bias
			sum += network.layers[i].neurons[j].bias;
			// sigmoid function to the value
			network.layers[i].neurons[j].activation = sigmoid(sum);
			sum = 0;
		}
	}
	double *output_tab;
	output_tab = malloc(sizeof(double) * (network.layers[network.nb_layers - 1].nb_neurons + 1));
	for(unsigned int i = 0; i < network.layers[network.nb_layers - 1].nb_neurons; i++){
		for(unsigned int j = 0; j < network.layers[network.nb_layers - 1].neurons[i].nb_weights; j++){
			sum += network.layers[network.nb_layers - 2].neurons[j].activation *
			 network.layers[network.nb_layers - 1].neurons[i].weights[j];
		}
		sum += network.layers[network.nb_layers - 1].neurons[i].bias;
		output_tab[i] = sum;
		sum = 0;
	}
	softmax(output_tab, network.layers[network.nb_layers - 1].nb_neurons);
	// I need to add the softmax function somewhere here
	for(unsigned int i = 0; i < network.layers[network.nb_layers - 1].nb_neurons; i++){
		printf("the output neuron number %i as a probability of: %f\n", i + 1,
		output_tab[i]);
	}
}

double sigmoid(double x){
	return 1 / (1 + (exp(-1 * x)));
}

double sigmoid_prime(double x){
	return sigmoid(x) * (1 - sigmoid(x));
}

double* softmax(double arr[], int size){
	double max = arr[0];
	for(int i = 1; i < size; i++){
		if(max < arr[i]){
			max = arr[i];
		}
	}
	for(int i = 0; i < size; i++){
	arr[i] = arr[i] - max;
	}
	double divisor = 0;
	for(int i = 0; i < size; i++){
		divisor += (exp(arr[i]));
	}
	for(int i = 0; i < size; i++){
		arr[i] = (exp(arr[i])) / divisor;
	}
	return arr;
}
