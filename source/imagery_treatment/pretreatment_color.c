#include <err.h>                                                                
#include <SDL/SDL.h>                                                            
#include "SDL/SDL_image.h"                                                      
#include "pixel_operations.h"                                                   
#include "sdl_functions.h"
#include <math.h>

Uint32 contrast_p(Uint32 pixel, double fact){
	if(pixel<=255/2)                                        
        pixel=(Uint32)((255/2)*pow((double)2*pixel/255,fact));
        else                                                    
        pixel=255-contrast_p((Uint32)(255-pixel),fact);
	return pixel;


}

void contrast(SDL_Surface *image_surface, int fact){                                     
        for(int i = 0; i<image_surface->w;i++){                                 
             for(int j = 0; j<image_surface->h;j++){
			Uint32 pixel = get_pixel(image_surface, i, j);
			for(int x=0;x<=fact;x++){
				if(pixel>=(Uint32)(x*(255.f/fact))
					&& pixel<=(Uint32)((x+1)*(255.f/fact))){
					pixel=((x+1)*(255.f/fact));
					}
				}
			//pixel=contrast_p(pixel,fact);
			put_pixel(image_surface, i, j, pixel);
             }                                                                  
     }                                                                          
}
void invert(SDL_Surface *image){
	for(int i = 0; i<image->w;i++){                                         
                for(int j = 0; j<image->h;j++){                                 
                        Uint32 pixel = get_pixel(image, i, j);                  
                        Uint8 r, g, b;                                          
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			pixel = SDL_MapRGB(image->format,255-r,255-g,255-b);
			put_pixel(image, i, j, pixel);
		}
	}
}
float color_max(SDL_Surface *image){
	float max=0;
	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			Uint32 pixel = get_pixel(image, i, j);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if(r>max){
				max=r;
			}
		}
	}
	return max;
}

void brightness(SDL_Surface *image){

	float max= color_max(image);
	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			Uint32 pixel = get_pixel(image, i, j);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			pixel = SDL_MapRGB(image->format,255-r*(255/max),
			255-r*(255/max),255-r*(255/max));
			put_pixel(image, i, j, pixel);
		}
	}
}

int median(int *array){
	return array[(9-1)/2];
}
int ave(int*array){
	int res=0;
	for(int i=0;i<9;i++){
		res+=array[i];
	}
	return res/9;
}
void median_filter(SDL_Surface *image){

	for(int i = 0; i<image->h;i++){
		for(int j = 0; j<image->w;j++){
			int *neighbours=get_neighbours_pixel(image,i,j);
			sort_swap(neighbours,9);
			int pixel=median(neighbours);
			put_pixel(image,i,j,(Uint32)pixel);
		}
	}
}


void aver_filter(SDL_Surface *image){

	for(int i = 0; i<image->h;i++){
		for(int j = 0; j<image->w;j++){
			int *neighbours=get_neighbours_pixel(image,i,j);
			sort_swap(neighbours,9);
			int pixel=ave(neighbours);
			put_pixel(image,i,j,(Uint32)pixel);
		}
	}
}

int otsu_tresholding(SDL_Surface *image){
	float histogram[256]={0.0f};
	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			Uint32 pixel = get_pixel(image, i, j);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			size_t grey=r;
			histogram[grey]+=1;
		}
	}
	int tot_pix=(image->w)*(image->h);
	float sum=0;
	for(int i=0; i<256;i++){
		sum+=i*histogram[i];
	}
	float sumB=0;
	int wB=0;
	int wF=0;
	float varMax=0;
	int treshold=0;
	for(int i=0;i<256;i++){
		wB+=histogram[i];   //weight background
		if(wB==0){
			continue;
		}
		wF=tot_pix - wB;    //weight foreground
		if(wF==0){
			break;
		}
		sumB+=(float)(i*histogram[i]);
		float mB=sumB/wB;   //mean background
		float mF=(sum-sumB)/wF;  //mean foreground
		
		//Calcul between class variance
		float varBetween=(float)wB*(float)wF*(mB-mF)*(mB-mF);
		if(varMax<varBetween){
			varMax=varBetween;
			treshold=i;
		}
	}
	return treshold;
}

void binarize(SDL_Surface *image){
	int tresh=otsu_tresholding(image);
	int black_p=0;
	int white_p=0;
	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			Uint32 pixel = get_pixel(image, i, j);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			Uint32 bin_p=0;
			if(r<tresh){
				black_p++;
			}
			else{
				bin_p=255;
				white_p++;
			}
			pixel=SDL_MapRGB(image->format,bin_p,bin_p,bin_p);
			put_pixel(image,i,j,pixel);

		}
	}
	if(black_p>white_p){
		for(int i = 0; i<image->w;i++){
			for(int j = 0; j<image->h;j++){
				Uint32 pixel = get_pixel(image, i, j);
				Uint8 r, g, b;
                        	SDL_GetRGB(pixel, image->format, &r, &g, &b);
				Uint32 bin_p=0;
				if(r==0){
					bin_p=255;
				}
				pixel=SDL_MapRGB(image->format,bin_p,bin_p,
				bin_p);
				put_pixel(image,i,j,pixel);
			}
		}
	}
}







