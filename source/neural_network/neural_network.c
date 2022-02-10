#include <math.h>
#include <err.h>
#include <stddef.h>
#include <stdlib.h>
#include "../../include/neural_network/neural_network.h"

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
	
	layer.neurons = malloc(sizeof(Neuron) * previous_layer_size);

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
	
	/* checking if network has a good format */
	if(nb_layers < 3){
		errx(1, "Bad neural network format");
		}
	for(unsigned int i = 0; i < nb_layers; i++){
		if (sizes[i] == 0){
			errx(1, "Bad neural network format");
			}
		}

	network.layers = malloc(sizeof(Layer) * nb_layers);
	/* create layers for network */
	network.layers[0] = newLayer(sizes[0], 0);
	for(unsigned int i = 1; i < nb_layers; i++){
		network.layers[i] = newLayer(sizes[i], sizes[i - 1]);
		}
	
	return network;
	}


/* void feedforward(Network network){

	} */

double sigmoid(double x){
	return 1 / (1 +	exp(-1 * x));
	}

double sigmoid_prime(double x){
	return sigmoid(x) * (1 - sigmoid(x));
	}

double* softmax(double arr[], int size){
	double divisor = 0;
	for(int i = 0; i < size; i++){
		divisor += exp(arr[i]);
		}
	for(int i = 0; i < size; i++){
		arr[i] = exp(arr[i]) / divisor;
		}
	return arr;
	}

