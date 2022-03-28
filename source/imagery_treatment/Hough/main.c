#include <math.h>                                                               
#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include "sdl_functions.h"                                                      
                                                                                
#include "pixel_operations.h"                                                   
#include "SDL/SDL_image.h"                                                      
#include "SDL/SDL.h"
#include "segmentation.h"									                                                            
int main(){
    SDL_Surface* image_surface;                                                 
    SDL_Surface* screen_surface;                                                
                                                                                
    init_sdl();                                                                 
                                                                               
    image_surface = load_image("my_image.png");                                 
    screen_surface = display_image(image_surface);                              
                                                                                
    wait_for_keypressed();
    //Uint32 red = SDL_MapRGB(image_surface->format,255,0,0);                                                      
    draw_line(image_surface,0,0,1000,1000);                                                   
    //wait_for_keypressed();
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    //hough_transform(image_surface);
    SDL_FreeSurface(image_surface);                                             
    SDL_FreeSurface(screen_surface);
	return 0;
}
