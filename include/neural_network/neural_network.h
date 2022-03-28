#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <err.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

typedef struct Neuron{
	unsigned int nb_weights;
	double bias, activation, delta;
	double* weights;
} Neuron;

Neuron* newNeuron(unsigned int nb_weights);



typedef struct Layer{
	unsigned int nb_neurons;
	Neuron** neurons;
} Layer;

Layer* newLayer(unsigned int size, unsigned int previous_layer_size);



typedef struct Network{
	unsigned int nb_layers;
	Layer** layers;
} Network;

Network* newNetwork(unsigned int sizes[], unsigned int nb_layers);

Network* initNetwork(unsigned int sizes[], unsigned int nb_layers);

void freeNetwork(Network* network);


void front_propagation(Network* network, double inputs[]);

double sigmoid(double x);

double sigmoid_prime(double x);

void softmax(Layer* layer);

double cost_function(Network* network, double expected[]);

void back_propagation(Network* network, double expected[]);

void update(Network* network, double eta);


#endif
