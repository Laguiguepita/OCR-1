#include "math.h"
#include "../../include/neural_network/neural_network.h"

Neuron newNeuron(unsigned int nb_weights){
	Neuron neuron = {
		.nb_weights = nb_weights,
		.weights = NULL,
		.bias = 0,
		.activation = 0
		}
	return neuron;
	}


Layer newLayer(unsigned int size, unsigned int previous_layer_size){
	Layer layer = {
		.nb_neurons = size,
		.neurons = NULL
		}

	/* create neurons for layer */
	for(int i = 0; i < size; i++){
		layer.neurons[i] = newNeuron(previous_layer_size)
		}

	return layer;
	}

Network newNetwork(unsigned int sizes[]){
	Network network = {
		.nb_layers = sizeof(sizes) / sizeof(sizes[0]),
		.sizes = sizes,
		.layers = NULL
		}
	
	/* checking if network has a good format */
	if(network.nb_layers < 3){
		errx(EXIT_FAILURE, "Bad neural network format");
		}
	for(int i = 0; i < network.nb_layers; i++){
		if (sizes[i] == 0){
			errx(EXIT_FAILURE, "Bad neural network format")
			}
		}
	/* create layers for network */
	network.layers[0] = newLayer(sizes[0], 0);
	for(int i = 1; i < network.nb_layers; i++){
		network.layers[i] = newLayer(sizes[i], sizes[i - 1]);
		}
	
	return network;
	}


void feedforward(Network network){

	}


double sigmoid(double x){
	return 1 / (1 +	exp(-1 * x));
	}

double sigmoid_prime(double x){
	return sigmoid(x) * (1 - sigmoid(x));
	}

int* softmax(double x[]){
	double divisor = 0;
	int nb = sizeof(x) / sizeof(x[0]);
	for(int i = 0; i < nb; i++){
		divisor += exp(x[i]);
		}
	double a[nb];
	for(int i = 0; i < nb; i++){
		a[i] = exp(x[i]) / divisor;
		}
	return *a;
	}

