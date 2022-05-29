#include <stdio.h>
#include <dirent.h>
#include "from_N_to_S.h"
#include "stdlib.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../../include/neural_network/save_and_load.h"
#include "../../include/neural_network/neural_network.h"
#include "../../include/sudoku_solver/solver.h"
#include "../imagery_treatment/Pretreatment/image_operations.h"
#include "../imagery_treatment/Hough/segmentation.h"


struct list *cell_to_list(char path[])
{
	DIR *dr;
	struct dirent *de;
	dr = opendir(path);
	if (dr == NULL)
	{
		printf("Could not open current directory" );
		return 0;
	}
	
		
	
	struct list *p = malloc(sizeof(char)*6);
	size_t i = 0;
	while ((de = readdir(dr)) != NULL)
		{
			if (de->d_name[0] != '.')
				{
					for (int j = 0; j < 6; j++)
						p[i].name[j] = de->d_name[j];
					
					i++;
				}
		}
	p[i+1].name[0] = '\0';
	
	printf("2\n");
	closedir(dr);
	
	return p;
}



double* auxiliaire(char path[])
{
	SDL_Surface *img;
	img = load_image(path);
	double *p = calloc (784,sizeof(double));
	
	for (size_t i = 0; i < 28; i++)
			for (size_t j = 0; j < 28; j++)
		p[i*28+j] = (double)get_pixel(img, i, j);

	return p;
	
	
}



void list_to_file(struct list *list, int matrix[])
{
	
	size_t i = 0;
	
	int nombre;
	
	printf("3\n");
	Network *network = loadNetwork("../neural_network/saves/test1");
	printf("3,5\n");
	while(list[i].name[0] != '\0')
	{
		nombre = (list[i].name[5] - '0') * 10 + (list[i].name[6] - '0');
		
		matrix[nombre] = front_propagation(network, auxiliaire(list[i].name));
		i++;
	}
	matrix_to_file(matrix, "Solve/sudoku_unsolved");
	
	freeNetwork(network);
	printf("4\n");
}



void main_from() {
	int* sudoku= calloc(81, sizeof(int));
	char path[] = "../imagery_treatment/Pretreatment/cells/";
	printf("1\n");
	list_to_file(cell_to_list(path), sudoku);
	free(sudoku);
}
void split(char *path){                                                         
                                                                                 
         SDL_Surface *img;                                                       
         init_sdl();                                                             
         img = load_image(path);                                                 
         int taillex = (img->w)/9;                                               
         int x=0;                                                                
         int y=0;                                                                
                                                                                 
         char cell[13] = "cells/cell00";                                         
         int t=1;                                                                        
         for(int i = 0;i<81;i++){                                                
                SDL_Surface* imagedest = SDL_CreateRGBSurface(0,taillex,taillex,32,0,0,0,0);
                 for (int o = x; o<x+taillex;o++){                               
                         for (int p = y; p<y+taillex;p++){                       
                                       Uint32 pixel= get_pixel(img,o,p);         
                                       put_pixel(imagedest,(o%taillex),(p%taillex),pixel);
                                }                                               
                                                                                 
                        }                                                       
                                                                                
                 printf("%d, %d, %d\n",i, i/10+'0', i%10+'0');                                             
                                                                                
                 cell[10]=i/10+'0';                                              
                 cell[11]=i%10+'0';
		 cell[12] = '\0';                                              

                 if (isTache(imagedest) == 1){
			Save_Image(imagedest,cell);                            
                         resize(cell);                                           
                 }                                                               
                                                                                
                                                                                 
                                                                                 
                 if (i==(t*9)-1){                                            
                        x=0;                                                    
                        y+=taillex;
			t++;                                             
                                                                                
                }                                                               
              else {                                                          
                         x+=taillex;                                             
                 }                                                               
                                                                                
                                                                                
         }                                                                       
                                                                                 
}                                                                               
         
