#ifndef DATA_SET_H
#define DATA_SET_H

#include "neural_network.h"

typedef struct Data_set{
    double **training_images, **test_images;
    unsigned char *training_labels, *test_labels;
} Data_set;


Data_set* initData_set();
void load_labels(Data_set* data, char path[], int isTrainingSet);
void load_images(Data_set* data, char path[], int isTrainingSet);
void freeData_set(Data_set *data);

#endif
