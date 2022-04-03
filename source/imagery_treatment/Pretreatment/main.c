#include <err.h>                                                                
#include "SDL/SDL.h"                                                            
#include "SDL/SDL_image.h"                                                      
#include "pixel_operations.h"                                                   
#include "sdl_functions.h"
#include "grayscale.h"
#include "pretreatment_color.h"
#include "../Hough/segmentation.h"
#include "../Hough/hough.h"

int main(){
    SDL_Surface* image_surface;                                                 
    SDL_Surface* screen_surface;                                                
    //SDL_Surface* image_surface2;                                                                             
    init_sdl();                                                                 
                                                                                
    image_surface = load_image("my_image.png");                                 
    screen_surface = display_image(image_surface);                              
    //image_surface2 = load_image("my_image.png"); 

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
    invert(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    //List *lines=initList();
    //lines=hough_transform(image_surface,image_surface2);
    //Line_sort(lines,30, image_surface);
    houghTransformation(image_surface);
    update_surface(screen_surface, image_surface);
    //SDL_Surface* image;
    detect(image_surface);
   /* SDL_Surface * image2;
    image2=load_image("final_square.bmp");
    detect(image2);
    wait_for_keypressed();
    update_surface(screen_surface ,image2);
    wait_for_keypressed();
    SDL_Surface * image3;
    image3=load_image("final_square.bmp");
    detect(image3);
    wait_for_keypressed();
    update_surface(screen_surface ,image3);
    wait_for_keypressed();
*/
    //update_surface(screen_surface, image);
    
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);                                             
    SDL_FreeSurface(screen_surface);
    
}
