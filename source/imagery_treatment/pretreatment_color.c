#include <err.h>                                                                
#include <SDL/SDL.h>                                                            
#include "SDL/SDL_image.h"                                                      
#include "pixel_operations.h"                                                   
#include "sdl_functions.h"
#include <math.h>

Uint32 contrast_p(Uint32 pixel, double fact){
	if(pixel<=255/2)                                        
        pixel=(Uint32)((255/2)*pow((double)2*pixel/255,fact));
        else                                                    
        pixel=255-contrast_p((Uint32)(255-pixel),fact);
	return pixel;


}

void contrast(SDL_Surface *image_surface, int fact){                                     
        for(int i = 0; i<image_surface->w;i++){                                 
             for(int j = 0; j<image_surface->h;j++){
			Uint32 pixel = get_pixel(image_surface, i, j);
			for(int x=0;x<=fact;x++){
				if(pixel>=(Uint32)(x*(255.f/fact))
					&& pixel<=(Uint32)((x+1)*(255.f/fact))){
					pixel=((x+1)*(255.f/fact));
					}
				}
			//pixel=contrast_p(pixel,fact);
			put_pixel(image_surface, i, j, pixel);
             }                                                                  
     }                                                                          
}
void invert(SDL_Surface *image){
	for(int i = 0; i<image->w;i++){                                         
                for(int j = 0; j<image->h;j++){                                 
                        Uint32 pixel = get_pixel(image, i, j);                  
                        Uint8 r, g, b;                                          
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			pixel = SDL_MapRGB(image->format,255-r,255-g,255-b);
			put_pixel(image, i, j, pixel);
		}
	}
}
float color_max(SDL_Surface *image){
	float max=0;
	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			Uint32 pixel = get_pixel(image, i, j);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if(r>max){
				max=r;
			}
		}
	}
	return max;
}

void brightness(SDL_Surface *image){

	float max= color_max(image);
	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			Uint32 pixel = get_pixel(image, i, j);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			pixel = SDL_MapRGB(image->format,255-r*(255/max),
			255-r*(255/max),255-r*(255/max));
			put_pixel(image, i, j, pixel);
		}
	}
}

int median(int *array){
	return array[(9-1)/2];
}
void median_filter(SDL_Surface *image){

	for(int i = 0; i<image->h;i++){
		for(int j = 0; j<image->w;j++){
			int *neighbours=get_neighbours_pixel(image,i,j);
			sort_swap(neighbours,9);
			int pixel=median(neighbours);
			put_pixel(image,i,j,(Uint32)pixel);
		}
	}
}



