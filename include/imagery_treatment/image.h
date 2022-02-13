#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct Pixel{
	unsigned int r, g ,b;
	struct Pixel *matrix;
}Pixel;

typedef struct Image{
	unsigned int width;
	unsigned int heigth;
	double average_color;
	Pixel **pixels;
	char *path;
}Image;

Image newImage(SDL_image *surface, int matrix, unsigned int width, unsigned int height);
#endif
