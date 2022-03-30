#include "../../include/neural_network/data_set.h"

#define MAX_LENGTH 10

void read_data(){
	// try to open the file
	FILE* file = NULL;
	file = fopen("bite", "rb");
	if(file == NULL){
		errx(1, "failed to open the file");
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


	unsigned char buffer2[10000];
	fread(buffer2,sizeof(buffer2), 1, file);
	for(size_t i = 0; i < 10000; i++){
		printf("%u ", buffer2[i]);
	}



	
	// close the file
	fclose(file);
}
