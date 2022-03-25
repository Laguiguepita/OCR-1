#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H
#include"SDL/SDL.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"SDL/SDL_image.h"

void init_sdl();  
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img); 
void wait_for_keypressed(); 
void SDL_FreeSurface(SDL_Surface *surface); 
void draw_pixel(SDL_Surface *surface, int x, int y, Uint32 color);
void swap(int *i, int *j);
void draw_line(SDL_Surface *surface,int x1,int y1,int x2,int y2, Uint32 color);  



#endif
