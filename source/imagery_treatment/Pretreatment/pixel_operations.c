// Simple get/put pixel for SDL
// Inspired by code from SDL documentation
// (http://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html)

#include <err.h>
#include "pixel_operations.h"

static inline
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

int* get_neighbours_pixel(SDL_Surface *image,int i,int j){
	static int neighbours[9]={0,0,0,0,0,0,0,0,0};
	if(i==0){
		if(j==0){
			neighbours[0]=get_pixel(image,i,j+1);
			neighbours[1]=get_pixel(image,i+1,j);
			neighbours[2]=get_pixel(image,i+1,j+1);
		}
		else if(j==(image->w)-1){
			neighbours[0]=get_pixel(image,i,j-1);
			neighbours[1]=get_pixel(image,i+1,j-1);
			neighbours[2]=get_pixel(image,i+1,j);
		}
		else{
			neighbours[0]=get_pixel(image,i,j-1);
			neighbours[1]=get_pixel(image,i+1,j-1);
			neighbours[2]=get_pixel(image,i+1,j);
			neighbours[3]=get_pixel(image,i+1,j+1);
			neighbours[4]=get_pixel(image,i,j+1);
		}
	}
	else if(i==(image->h)-1){
		if(j==0){
			neighbours[0]=get_pixel(image,i-1,j+1);
			neighbours[1]=get_pixel(image,i-1,j);
			neighbours[2]=get_pixel(image,i,j+1);
		}
		else if(j==(image->w)-1){
			neighbours[0]=get_pixel(image,i,j-1);
			neighbours[1]=get_pixel(image,i-1,j-1);
			neighbours[2]=get_pixel(image,i-1,j);
		}
		else{
			neighbours[0]=get_pixel(image,i-1,j+1);
			neighbours[1]=get_pixel(image,i-1,j);
			neighbours[2]=get_pixel(image,i,j+1);
			neighbours[3]=get_pixel(image,i-1,j-1);
			neighbours[4]=get_pixel(image,i,j-1);
		}
	}
	else{
		if(j==0){
			neighbours[0]=get_pixel(image,i-1,j);
			neighbours[1]=get_pixel(image,i-1,j+1);
			neighbours[2]=get_pixel(image,i,j+1);
			neighbours[3]=get_pixel(image,i+1,j+1);
			neighbours[4]=get_pixel(image,i+1,j);
		}
		else if(j==(image->w)-1){
			neighbours[0]=get_pixel(image,i-1,j-1);
			neighbours[1]=get_pixel(image,i-1,j);
			neighbours[2]=get_pixel(image,i,j-1);
			neighbours[3]=get_pixel(image,i+1,j-1);
			neighbours[4]=get_pixel(image,i+1,j);
		}
		else{
			neighbours[0]=get_pixel(image,i-1,j-1);
			neighbours[1]=get_pixel(image,i-1,j);
			neighbours[2]=get_pixel(image,i-1,j+1);
			neighbours[3]=get_pixel(image,i,j-1);
			neighbours[4]=get_pixel(image,i,j+1);
			neighbours[5]=get_pixel(image,i+1,j-1);
			neighbours[6]=get_pixel(image,i+1,j);
			neighbours[7]=get_pixel(image,i+1,j+1);
		}
	}
	neighbours[8]=get_pixel(image,i,j);
	return neighbours;
}
void sort_swap(int *array,int size){

	int i,j,k,c;
	for(i=1;i<size;i++) {

    		if ( array[i] < array[i-1] ) { 
        		j = 0;
        		while ( array[j] < array[i] ) j++;
 
 	c = array[i]; 
        	for( k = i-1 ; k >= j ; k-- ) array[k+1] = array[k];
	 array[j] = c; 
   		 }	
	}
}
