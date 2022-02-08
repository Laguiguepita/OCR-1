#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H


typedef struct Neuron{
	unsigned int nb_weights;
	signed int weights[];
	signed int bias;
	double activation;
} Neuron;


typedef struct Layer{
	unsigned int nb_neurons;
	Neuron neurons[];
} Layer;


typedef struct Network{
	unsigned int nb_layers;
	unsigned int sizes[];
	Layer layers[];
} Network;

double sigmoid(double x);

double sigmoid_prime(double x);


#endif
