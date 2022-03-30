#include "../../include/neural_network/data_set.h"

void load_label(){
	// try to open the file
	FILE* file = NULL;
	file = fopen("bite", "rb");
	if(file == NULL){
		errx(EXIT_FAILURE, "failed to open the file");
	}
	
	unsigned char buffer[8];
	fread(buffer, sizeof(buffer), 1, file);

	for(size_t i = 0; i < 8; i++){
		printf("%u ", buffer[i]);
	}
	printf("\n");


	// big-edian
	int magicNumber;
	magicNumber = (buffer[0]<<24) + (buffer[1]<<16) + (buffer[2]<<8) + buffer[3];

	printf("%i\n", magicNumber);

	int numberOfItems;
	numberOfItems = (buffer[4]<<24) + (buffer[5]<<16) + (buffer[6]<<8) + buffer[7];

	printf("%i\n", numberOfItems);


	unsigned char buffer2[numberOfItems];
	fread(buffer2, sizeof(buffer2), 1, file);
	for(int i = 0; i < numberOfItems; i++){
		printf("%u ", buffer2[i]);
	}

	// close the file
	fclose(file);
}

void load_image(){
	// try to open the file
	FILE* file = NULL;
	file = fopen("bite1", "rb");
	if(file == NULL){
		errx(EXIT_FAILURE, "failed to open the file");
	}

	unsigned char buffer[16];
	fread(buffer, sizeof(buffer), 1, file);
	for(size_t i = 0; i < 16; i++){
		printf("%u ", buffer[i]);
	}
	printf("\n");

	// big-edian
	int magicNumber;
	magicNumber = (buffer[0]<<24) + (buffer[1]<<16) + (buffer[2]<<8) + buffer[3];

	printf("%i\n", magicNumber);

	int numberOfImages;
	numberOfImages = (buffer[4]<<24) + (buffer[5]<<16) + (buffer[6]<<8) + buffer[7];

	printf("%i\n", numberOfImages);

	int numberOfRows;
	numberOfRows = (buffer[8]<<24) + (buffer[9]<<16) + (buffer[10]<<8) + buffer[11];

	printf("%i\n", numberOfRows);

	int numberOfColumns;
	numberOfColumns = (buffer[12]<<24) + (buffer[13]<<16) + (buffer[14]<<8) + buffer[15];

	printf("%i\n", numberOfColumns);

	unsigned char buffer2[numberOfImages * numberOfRows * numberOfColumns];
	fread(buffer2, sizeof(buffer2), 1, file);



	unsigned char (*imageList)[28][28];
	imageList = malloc(numberOfImages * sizeof(*imageList));
	/*
	for(int i = 0; i < numberOfImages * numberOfRows * numberOfColumns; i++){
		printf("%i - %u\n", i, buffer2[i]);
	}
	*/


	for(int i = 0; i < numberOfImages - 1; i++){
		for(int j = 0; j < numberOfRows - 1; j++){
			for(int l = 0; l < numberOfColumns - 1; l++){
				imageList[i][j][l] =
				buffer2[i * numberOfRows * numberOfColumns
				+ j * numberOfColumns + l];
			}
		}
	}

	print_image(imageList[3]);

	// close the file
	fclose(file);
}


void print_image(unsigned char image[28][28]){
	for(int i = 0; i < 28; i++){
		for(int j = 0; j < 28; j++){
			printf("%3u ", image[i][j]);
		}
		printf("\n");
	}
}
