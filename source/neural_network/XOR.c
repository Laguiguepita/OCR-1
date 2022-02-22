#include "../../include/neural_network/XOR.h"


double log_loss(double results[], double expected_results[], size_t length){
	double sum = 0;
	double m = 0;
	for(size_t i = 0; i < length; i++){
		sum += expected_results[i] * log(results[i]) +
		       	(1 - expected_results[i]) * log(1 - results[i]);
		m++;
	}
	return (-1 / m) * sum;
}

double feedforward(Network* network, double inputs[]){
	// add the inputs in the neural network
	for(unsigned int i = 0; i < network->layers[0]->nb_neurons; i++){
		network->layers[0]->neurons[i]->activation = inputs[i];
	}

	// proceed to the feedforward
	double sum = 0;
	for(unsigned int i = 1; i < network->nb_layers; i++){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			for(unsigned int l = 0;
				       	l < network->layers[i]->neurons[j]->nb_weights;l++){
				sum += network->layers[i-1]->neurons[l]->activation *
					network->layers[i]->neurons[j]->weights[l];
			}
			sum += network->layers[i]->neurons[j]->bias;
			network->layers[i]->neurons[j]->activation = sigmoid(sum);
			sum = 0;
		}
	}

	// return the activation of the output neuron
	printf("the activation of the neuron is: %f\n",
		       	network->layers[network->nb_layers - 1]->neurons[0]->activation);
	return network->layers[network->nb_layers - 1]->neurons[0]->activation;
}


void gradients(){

}


void update(){

}
