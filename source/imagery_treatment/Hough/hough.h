#ifndef HOUGH_H
#define HOUGH_H
#include "sdl_functions.h"
void houghTransformation(char *path);
int right_corner(SDL_Surface *image,int i,int j);
int bottom_corner(SDL_Surface *image,int i,int j);
void detect(SDL_Surface *image);

#endif
