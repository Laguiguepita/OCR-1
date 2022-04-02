#include <math.h>
#include "../../include/neural_network/neural_network.h"


// -----------------------NEURAL NETWORK STRUCT------------------------
Neuron* newNeuron(unsigned int nb_weights){
	// allocating memory for the neuron
	Neuron* neuron = NULL;
	neuron = malloc(sizeof(Neuron));
	if(neuron == NULL){
		errx(EXIT_FAILURE, "Not enough memory!");
	}

	// init the neuron values
	neuron->nb_weights = nb_weights;
	neuron->bias = 0;
	neuron->activation = 0;
	neuron->delta = 0;
	neuron->weights = NULL;

	// allocating memory for the weights
	neuron->weights = malloc(sizeof(double) * nb_weights);
	if(neuron->weights == NULL){
		errx(EXIT_FAILURE, "Not enough memory!");
	}

	// to init weights you should use initNetwork() or loadNetwork function

	return neuron;
}


Layer* newLayer(unsigned int size, unsigned int previous_layer_size){
	// allocating memory for the layer
	Layer* layer = NULL;
	layer = malloc(sizeof(Layer));
	if(layer == NULL){
		errx(EXIT_FAILURE, "Not enough memory!");
	}

	// init the layer values
	layer->nb_neurons = size;
	layer->neurons = NULL;
	
	// allocating memory for the neurons
	layer->neurons = malloc(sizeof(Neuron*) * size);
	if(layer->neurons == NULL){
		errx(EXIT_FAILURE, "Not enough memory!");
	}

	// create neurons for layer
	for(unsigned int i = 0; i < size; i++){
		layer->neurons[i] = newNeuron(previous_layer_size);
	}
	
	return layer;
}

Network* newNetwork(unsigned int sizes[], unsigned int nb_layers){
	// allocating memory for the network
	Network* network = NULL;
	network = malloc(sizeof(Network));
	if(network == NULL){
		errx(EXIT_FAILURE, "Not enough memory!");
	}

	// init the network values
	network->nb_layers = nb_layers;
	network->nb_layers = nb_layers;
	network->layers = NULL;
	
	// checking if network has a good format
	if(nb_layers < 3){
		errx(EXIT_FAILURE, "Bad neural network format");
	}
	for(unsigned int i = 0; i < nb_layers; i++){
		if (sizes[i] == 0){
			errx(EXIT_FAILURE, "Bad neural network format");
		}
	}

	// allocating memory for the layers
	network->layers = malloc(sizeof(Layer*) * nb_layers);
	if(network->layers == NULL){
		errx(EXIT_FAILURE, "Not enough memory!");
	}

	// create layers for network
	network->layers[0] = newLayer(sizes[0], 0);
	for(unsigned int i = 1; i < nb_layers; i++){
		network->layers[i] = newLayer(sizes[i], sizes[i - 1]);
	}
	
	return network;
}



Network* initNetwork(unsigned int sizes[], unsigned int nb_layers){
	Network* network = newNetwork(sizes, nb_layers);

	srand(time(NULL));
	for(unsigned int i = 1; i < network->nb_layers; i++){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			for(unsigned int l = 0;
			l < network->layers[i]->neurons[j]->nb_weights; l++){
				network->layers[i]->neurons[j]->weights[l] =
				 ((double)rand()/(double)(RAND_MAX)) * 3 
				 * pow(-1, rand() % 2);
			}
			network->layers[i]->neurons[j]->bias =
			 ((double)rand()/(double)(RAND_MAX)) * 3
			 * pow(-1, rand() % 2);
		}
	}

	return network;
}


void freeNetwork(Network* network){
	for(unsigned int i = 0; i < network->nb_layers; i++){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			free(network->layers[i]->neurons[j]->weights);
		}
		free(network->layers[i]->neurons);
	}
	free(network->layers);
	free(network);
}

// -------------------------ACTIVATION FUNCTIONS---------------------------
double sigmoid(double x){
	return 1 / (1 + (exp(-1 * x)));
}

double sigmoid_prime(double x){
	// admeting that x variable is the activation so x = sigmoid(x')
	return x * (1 - x);
}

void softmax(Layer* layer){
	unsigned int nb_neurons = layer->nb_neurons;

	// try to find the max value of neurons
	double max = layer->neurons[0]->activation;
	for(unsigned int i = 1; i < nb_neurons; i++){
		if(max < layer->neurons[i]->activation){
			max = layer->neurons[i]->activation;
		}
	}

	// substract all neurons value by the max value found
	for(unsigned int i = 0; i < nb_neurons; i++){
	layer->neurons[i]->activation = layer->neurons[i]->activation - max;
	}

	// calculate the divisor of the softmax function
	double divisor = 0;
	for(unsigned int i = 0; i < nb_neurons; i++){
		divisor += (exp(layer->neurons[i]->activation));
	}

	// calculate the value for each neurons
	for(unsigned int i = 0; i < nb_neurons; i++){
		layer->neurons[i]->activation = 
			(exp(layer->neurons[i]->activation)) / divisor;
	}
}

// ----------------------------NEURAL NETWORK FUNCTIONS-----------------------
void front_propagation(Network* network, double inputs[]){
	// add the inputs in the neural network
	unsigned int nb_layers = network->nb_layers;
	for(unsigned int i = 0; i < network->layers[0]->nb_neurons; i++){
	network->layers[0]->neurons[i]->activation = inputs[i];
	}
	double sum = 0;
	// proceed to the front_propagation for the hiddens layers
	// the loop don't go into the first layer and the last layer
	for(unsigned int i = 1; i < nb_layers - 1; i++){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			for(unsigned int l = 0;
			l < network->layers[i]->neurons[j]->nb_weights; l++){
				/* i.e. activation of the neuron in the previous 
				layer multiply by the weight of the actual neuron */
				sum += network->layers[i-1]->neurons[l]->activation *
				network->layers[i]->neurons[j]->weights[l];
			}
			// add the bias
			sum += network->layers[i]->neurons[j]->bias;
			// sigmoid function to the value
			network->layers[i]->neurons[j]->activation = sigmoid(sum);
			sum = 0;
		}
	}
	// same as upper but we don't do the sigmoid func
	for(unsigned int i = 0; i < network->layers[nb_layers - 1]->nb_neurons; i++){
		for(unsigned int j = 0;
			       j < network->layers[nb_layers - 1]->neurons[i]->nb_weights;
			       j++){
			sum += network->layers[nb_layers - 2]->neurons[j]->activation *
			 network->layers[nb_layers - 1]->neurons[i]->weights[j];
		}
		sum += network->layers[nb_layers - 1]->neurons[i]->bias;
		network->layers[nb_layers - 1]->neurons[i]->activation = sum;
		sum = 0;
	}
	softmax(network->layers[nb_layers - 1]);
	for(unsigned int i = 0; i < network->layers[nb_layers - 1]->nb_neurons; i++){
		printf("the output neuron number %i as a probability of: %f\n", i + 1,
		network->layers[network->nb_layers - 1]->neurons[i]->activation);
	}
}


// ------------------------NEURAL NETWORK LEARNING FUNCTIONS-------------------
double cost_function(Network* network, double expected[]){
	double cost = 0;
	for(unsigned int i = 0; i < network->layers[network->nb_layers - 1]->nb_neurons; i++){
		cost += 
		(network->layers[network->nb_layers - 1]->neurons[i]->activation - expected[i]) *
		(network->layers[network->nb_layers - 1]->neurons[i]->activation - expected[i]);
	}
	return cost;
}


void back_propagation(Network* network, double expected[]){
	// the output layer
	for(unsigned int i = 0; i < network->layers[network->nb_layers - 1]->nb_neurons; i++){
		network->layers[network->nb_layers - 1]->neurons[i]->delta =
		2 * (network->layers[network->nb_layers - 1]->neurons[i]->activation - expected[i]) *
		sigmoid_prime(network->layers[network->nb_layers - 1]->neurons[i]->activation);
	}
	// all the hiden layers
	for(unsigned int i = network->nb_layers - 2; i > 0; i--){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			double sum = 0;
			for(unsigned int l = 0; l < network->layers[i+1]->nb_neurons; l++){
				sum += network->layers[i+1]->neurons[l]->delta *
				network->layers[i+1]->neurons[l]->weights[j];
			}
			network->layers[i]->neurons[j]->delta = sum * 
			sigmoid_prime(network->layers[i]->neurons[j]->activation);
		}
	}
}

void update(Network* network, double eta){
	// all the layers excepted the input layers
	for(unsigned int i = network->nb_layers - 1; i > 0; i--){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			for(unsigned int l = 0; l
			< network->layers[i]->neurons[j]->nb_weights; l++){
				network->layers[i]->neurons[j]->weights[l] -=
				eta *
				network->layers[i]->neurons[j]->delta *
				network->layers[i-1]->neurons[l]->activation;
			}
			network->layers[i]->neurons[j]->bias -=
			eta *
			network->layers[i]->neurons[j]->delta;
		}
	}
}
