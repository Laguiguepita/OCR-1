#ifndef PIXEL_H
#define PIXEL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint32 get_pixel(SDL_Surface *surface, unsigned i, unsigned j);

#endif
