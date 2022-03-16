#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "sdl_functions.h"

void grayscale(SDL_Surface *image_surface){
	for(int i = 0; i<image_surface->h;i++){                                     
             for(int j = 0; j<image_surface->w;j++){                             
                     Uint32 pixel = get_pixel(image_surface, i, j);              
                     Uint8 r, g, b;                                              
                     SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);       
                     float average = 0.3*r + 0.59*g + 0.11*b;                    
                     Uint32 pixel2 = SDL_MapRGB(image_surface->format, average, average, average);
                     put_pixel(image_surface, i, j, pixel2);                     
             }                                                                   
     } 
}
