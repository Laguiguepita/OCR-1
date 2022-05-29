#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_rotozoom.h>
#include<SDL/SDL_image.h>
#include<string.h>
#include "../Pretreatment/image_operations.h"
void manual_rotation(char *path, double angle){
	SDL_Surface *image;
	init_sdl();
	image=load_image(path);
	image = rotozoomSurface(image,angle,1.0,1.0);
	Save_Image(image,path);
}

/*int main(){
	SDL_Surface *image;
	char path[255];
	double angle;
	printf("Donnez le nom de l'image ainsi que son path\n");
	if (scanf("%254s", path) != 1)
    {
        printf("Erreur lors de la saisie\n");
        return EXIT_FAILURE;
    }
	image=IMG_Load(path);
	printf("Donnez l'angle de rotation de l'image\n");
	scanf("%le\n",&angle);
	SDL_Surface *rotated=manual_rotation(image,angle);
	SDL_SaveBMP(rotated,"rotated_image");
	SDL_FreeSurface(rotated);
	SDL_FreeSurface(image);
	SDL_Quit();
	return 0;
}
*/
