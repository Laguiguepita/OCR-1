#ifndef HOUGH_H
#define HOUGH_H

void houghTransformation(SDL_Surface* image);
int right_corner(SDL_Surface *image,int i,int j);
int bottom_corner(SDL_Surface *image,int i,int j);
void detect(SDL_Surface *image);

#endif
