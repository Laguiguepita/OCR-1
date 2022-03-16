#ifndef PRETRATMENT_COLOR_H
#define PRETRATMENT_COLOR_H
void invert(SDL_Surface *image);
void contrast(SDL_Surface *image_surface, int fact);
float color_max(SDL_Surface *image);
void brightness(SDL_Surface *image);
#endif
