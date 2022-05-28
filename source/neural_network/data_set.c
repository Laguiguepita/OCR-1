#include "../../include/neural_network/data_set.h"

Data_set* initData_set(){
    // allocating memory for the data set
    Data_set* data = NULL;
    data = malloc(sizeof(Data_set));
    if(data == NULL){
        errx(EXIT_FAILURE, "Not enough memory!");
    }
    
    // init the data set values
    data->training_images = NULL;
    data->training_labels = NULL;
    data->test_images = NULL;
    data->test_labels = NULL;


    // allocate memory and collect data
    load_images(data, "./data/train-images", 1);
    load_labels(data, "./data/train-labels", 1);
    load_images(data, "./data/test-images", 0);
    load_labels(data, "./data/test-labels", 0);

    return data;
}


void load_labels(Data_set* data, char path[], int isTrainingSet){
	// try to open the file
	FILE* file = NULL;
	file = fopen(path, "rb");
	if(file == NULL){
		errx(EXIT_FAILURE, "failed to open the file");
	}
	
	unsigned char buffer[8];
	fread(buffer, sizeof(buffer), 1, file);


	// big-edian
/* NON ESSENTIAL
	int magicNumber;
	magicNumber = (buffer[0]<<24) + (buffer[1]<<16) + (buffer[2]<<8) + buffer[3];
*/

	int numberOfItems;
	numberOfItems = (buffer[4]<<24) + (buffer[5]<<16) + (buffer[6]<<8) + buffer[7];



    if(isTrainingSet == 1){
        // allocating memory
        data->training_labels = malloc(numberOfItems * sizeof(char));
        if(data->training_labels == NULL){
            errx(EXIT_FAILURE, "Not enough memory!");
        }
        
        fread(data->training_labels, numberOfItems, 1, file);
    }
    else{
        // allocating memory
        data->test_labels = malloc(numberOfItems * sizeof(char));
        if(data->test_labels == NULL){
            errx(EXIT_FAILURE, "Not enough memory!");
        }

        fread(data->test_labels, numberOfItems, 1, file);
    }

	// close the file
	fclose(file);
}

void load_images(Data_set* data, char path[], int isTrainingSet){
	// try to open the file
	FILE* file = NULL;
	file = fopen(path, "rb");
	if(file == NULL){
		errx(EXIT_FAILURE, "failed to open the file");
	}

	unsigned char buffer[16];
	fread(buffer, sizeof(buffer), 1, file);

	// big-edian
/* NON ESSENTIAL
	int magicNumber;
	magicNumber = (buffer[0]<<24) + (buffer[1]<<16) + (buffer[2]<<8) + buffer[3];
*/
	int numberOfImages;
	numberOfImages = (buffer[4]<<24) + (buffer[5]<<16) + (buffer[6]<<8) + buffer[7];

	int numberOfRows;
	numberOfRows = (buffer[8]<<24) + (buffer[9]<<16) + (buffer[10]<<8) + buffer[11];

	int numberOfColumns;
	numberOfColumns = (buffer[12]<<24) + (buffer[13]<<16) + (buffer[14]<<8) + buffer[15];

    
	unsigned char* buffer2 = NULL;
    buffer2 = malloc(numberOfImages * numberOfRows * numberOfColumns * sizeof(unsigned char));
    if(buffer2 == NULL){
        errx(EXIT_FAILURE, "Not enough memory!");
    }
	fread(buffer2, numberOfImages * numberOfRows * numberOfColumns, 1, file);


    if(isTrainingSet == 1){
        // allocate memory
        data->training_images = malloc(numberOfImages * sizeof(double*));
        if(data->training_images == NULL){
            errx(EXIT_FAILURE, "Not enough memory!");
        }
        
        for(int i = 0; i < numberOfImages; i++){
            data->training_images[i] = malloc(numberOfRows * numberOfColumns * sizeof(double));
            if(data->training_images[i] == NULL){
                errx(EXIT_FAILURE, "Not enough memory!");
            }
        }

        // insert elements
    	for(int i = 0; i < numberOfImages; i++){
	    	for(int j = 0; j < numberOfRows; j++){
		    	for(int l = 0; l < numberOfColumns; l++){
			    	data->training_images[i][j * 28 + l] =
				    buffer2[i * numberOfRows * numberOfColumns
			    	+ j * numberOfColumns + l];
		    	}
		    }
    	}
        
        
    }
    else{
        // allocate memory
        data->test_images = malloc(numberOfImages * sizeof(double*));
        if(data->test_images == NULL){
            errx(EXIT_FAILURE, "Not enough memory!");
        }
        
        for(int i = 0; i < numberOfImages; i++){
            data->test_images[i] = malloc(numberOfRows * numberOfColumns * sizeof(double));
            if(data->test_images[i] == NULL){
                errx(EXIT_FAILURE, "Not enough memory!");
            }
        }
        // insert elements
    	for(int i = 0; i < numberOfImages; i++){
	    	for(int j = 0; j < numberOfRows; j++){
		    	for(int l = 0; l < numberOfColumns; l++){
			    	data->test_images[i][j * 28 + l] =
			    	buffer2[i * numberOfRows * numberOfColumns
			    	+ j * numberOfColumns + l];
			    }
		    }
	    }
    }

    free(buffer2);

	// close the file
	fclose(file);
}

void freeData_set(Data_set *data){
	// free training labels
	free(data->training_labels);

	// free test labels
	free(data->test_labels);

	// free test images
	for(int i = 0; i < 10000; i++){
		free(data->test_images[i]);
	}
	free(data->test_images);

	// free training images
	for(int i = 0; i < 60000; i++){
		free(data->training_images[i]);
	}
	free(data->training_images);

	// free Data_set struct
	free(data);
}
