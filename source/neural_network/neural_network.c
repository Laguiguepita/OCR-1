#include "math.h"
#include "../../include/neural_network/neural_network.h"

Neuron newNeuron(unsigned int nb){
	Neuron neuron = {
		.nb_weights = nb,
		.weights = NULL,
		.bias = 0
		}
	return neuron;
	}


Layer newLayer(unsigned int nb){
	Layer layer = {
		.nb_neurons = nb,
		.neurons = NULL
		}
	return layer;
	}

Network newNetwork(unsigned int sizes[]){
	Network network = {
		.nb_layers = sizeof(sizes) / sizeof(sizes[0]),
		.sizes = sizes,
		.bias = NULL,
		.weights = NULL
		}
	return network;
	}


double sigmoid(double x){
	return 1 / (1 +	exp(-1 * x));
	}
