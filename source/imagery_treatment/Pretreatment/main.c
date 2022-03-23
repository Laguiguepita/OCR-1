#include <err.h>                                                                
#include "SDL/SDL.h"                                                            
#include "SDL/SDL_image.h"                                                      
#include "pixel_operations.h"                                                   
#include "sdl_functions.h"
#include "grayscale.h"
#include "pretreatment_color.h"

int main(){
    SDL_Surface* image_surface;                                                 
    SDL_Surface* screen_surface;                                                
                                                                                
    init_sdl();                                                                 
                                                                                
    image_surface = load_image("my_image.png");                                 
    screen_surface = display_image(image_surface);                              
                                                                                
    wait_for_keypressed();                                                      
    grayscale(image_surface);                                                   
    update_surface(screen_surface, image_surface);                              
    wait_for_keypressed();
    contrast(image_surface,10);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    invert(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    brightness(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    median_filter(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    //aver_filter(image_surface);
    //update_surface(screen_surface, image_surface);
    //wait_for_keypressed();
    otsu_tresholding(image_surface);
    //update_surface(screen_surface, image_surface);
    //wait_for_keypressed();
    binarize(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);                                             
    SDL_FreeSurface(screen_surface);

}
