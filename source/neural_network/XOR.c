#include "../../include/neural_network/XOR.h"

double XOR_front_propagation(Network* network, double inputs[]){
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
	//printf("the activation of the neuron is: %f\n",
	//	       	network->layers[network->nb_layers - 1]->neurons[0]->activation);
	return network->layers[network->nb_layers - 1]->neurons[0]->activation;
}

void XOR_back_propagation(Network* network, double expected[]){
	// the output layer
	for(unsigned int i = 0; i < network->layers[network->nb_layers - 1]->nb_neurons; i++){
		network->layers[network->nb_layers - 1]->neurons[i]->delta_temp =
		network->layers[network->nb_layers - 1]->neurons[i]->activation - expected[i];
		// ----------------------------------------------------
		network->layers[network->nb_layers - 1]->neurons[i]->delta_bias += 
		network->layers[network->nb_layers - 1]->neurons[i]->delta_temp;
		for(unsigned j = 0; j < network->layers[network->nb_layers - 1]->neurons[i]->nb_weights; j++){
			network->layers[network->nb_layers - 1]->neurons[i]->delta_weights[j] += 
			network->layers[network->nb_layers - 1]->neurons[i]->delta_temp *
			network->layers[network->nb_layers - 2]->neurons[j]->activation;
		}
	}
	// all the hiden layers
	for(unsigned int i = network->nb_layers - 2; i > 0; i--){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			double sum = 0;
			for(unsigned int l = 0; l < network->layers[i+1]->nb_neurons; l++){
				sum += network->layers[i+1]->neurons[l]->delta_temp *
				network->layers[i+1]->neurons[l]->weights[j];
			}
			network->layers[i]->neurons[j]->delta_temp = sum * 
			sigmoid_prime(network->layers[i]->neurons[j]->activation);
			// --------------------------------------------------
			network->layers[i]->neurons[j]->delta_bias +=
			network->layers[i]->neurons[j]->delta_temp;
			for(unsigned int l = 0; l < network->layers[i]->neurons[j]->nb_weights; l++){
				network->layers[i]->neurons[j]->delta_weights[l] +=
				network->layers[i]->neurons[j]->delta_temp *
				network->layers[i-1]->neurons[l]->activation;
			}
		}
	}
}


void XOR_training(Network* network, double eta, unsigned int epochs, unsigned int batchsize){
	double inputsList[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
	double expectedList[] = {0, 1, 1, 0};
	double cost = 0;

	for(unsigned int i = 0; i < epochs; i++){
		for(unsigned int j = 0; j < 4; j++){
			XOR_front_propagation(network, inputsList[j]);
			double expected[1] = {expectedList[j]};
			cost += cost_function(network, expected, 4);
			XOR_back_propagation(network, expected);
			if((j + 1) % batchsize == 0){
				update(network, eta, 5);
			}
		}
		if(i % 1000 == 0){
			printf("EPOCH NUMBER %i/%i\n", i, epochs);
			for(unsigned int j = 0; j < 4; j++){
				printf("%f XOR %f | result: %f | expected: %f\n",
				inputsList[j][0], inputsList[j][1], XOR_front_propagation(network,
				inputsList[j]), expectedList[j]);
 			}
			printf("the cost of the neural network is: %f\n\n", cost);
		}
		cost = 0;
	}
	printf("EPOCH NUMBER %i/%i\n", epochs, epochs);
		for(unsigned int j = 0; j < 4; j++){
			printf("%f XOR %f | result: %f | expected: %f\n",
			inputsList[j][0], inputsList[j][1], XOR_front_propagation(network,
			inputsList[j]), expectedList[j]);
			double expected[1] = {expectedList[j]};
			cost += cost_function(network, expected, 4);
 		}
		printf("the cost of the neural network is: %f\n", cost);
}
