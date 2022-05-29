#ifndef IMAGE_OPERATIONS_H_
#define IMAGE_OPERATIONS_H_

#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "math.h"
// Pixel operations

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface* screen, SDL_Surface* image);

// image operations

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
void wait_for_keydown();

// save and create

void Save_Image(SDL_Surface* img, char *name);
void Create_image(char *name, long width, long height, int red,
         int green, int blue);
void copy(char* path_img, char* path_toCopy);
void copy_surface(SDL_Surface* img, SDL_Surface* img2);
//void draw_line(SDL_Surface *surface,int x1,int y1,int x2,int y2);
#endif
