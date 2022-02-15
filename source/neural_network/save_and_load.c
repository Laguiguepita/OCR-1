#include <stdio.h>
#include <stdlib.h>

void saveNetwork(Network network){
    FILE* file = NULL;
    file = open("saves/save", "w");

    if(file != NULL){
    
    }
    else{
    printf("something goes wrong");
    }


    for(unsigned int i = 1; i < network.nb_layers; i++){
        for(unsigned int j = 0; j < network.layers[i].nb_neurons; j++){
            for(unsigned int l = 0; l < network.layers[i].neurons[j].nb_weights; l++){

            }
        }
    }


    fclose(file);
}
