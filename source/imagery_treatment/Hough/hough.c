#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdl_functions.h"
#include <err.h>
#include "pixel_operations.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "segmentation.h"

#define PI 3.14159265358979
void houghTransformation(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;
    int diagonale = floor(sqrt((double) (width * width + height * height)));

    // there will be 180 teta since we go from 0 include to 180 excluded
    // there will be diagonale rho
    int A[diagonale][180];
    for (int i = 0; i < diagonale; i++)
    {
        for (int j = 0; j < 180; j++)
        {
            A[i][j] = 0;
        }
    }

    for (double x = 10; x < width-10; x++)
    {
        for (double y = 10; y < height-10; y++)
        {
            Uint32 pixel = get_pixel(image, floor(x), floor(y));
            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            if (r > 10)
            {
                for (int teta = 0; teta < 180; teta++)
                {
                    double tetaRad = PI*(teta)/180.0;
                    //printf("floor(cos) = %i  teta = %i\n", rho, teta);
                    //if (x * (cos(tetaRad)) - y * (sin(tetaRad) + x * cos(tetaRad) + y * sin(tetaRad)) == 0)
                    {

                        int rho = abs((int) floor(x * cos(tetaRad) + y * sin(tetaRad)));
                        //printf("rho = %i\n", rho);
                        A[rho][teta] += 1;
                        //printf("long thing = %f cos(rho) = %i  cos(tetaRad) = %f  sin(tetaRad) = %f  x = %f  y = %f\n", x * (cos(tetaRad)) - y * (sin(tetaRad)) + rho, rho, cos(tetaRad), sin(tetaRad), x, y);
                        //printf("hello my bwuda 2\n");
                            /*for (int i = -1; i < 2; i++)
                            {
                                for (int j = -1; j < 2; j++)
                                {
                                    if (rho + i >= 0 && rho + i < diagonale && teta + j >= 0 && teta + j < 180)
                                    {
                                        //printf("hello my bwuda 3\n");
                                        A[rho + i][teta + j] += 1;
                                    }
                                }
                            }*/
                    }
                }
            }
        }
    }

    // EDGE DETECTION DONE

    //SDL_Surface* houghSpace = SDL_CreateRGBSurface(0, 180, diagonale, 32, 0, 0, 0, 0);
    //SDL_Surface* intersection = loadImage("output/blacknwhite.bmp");

    int Line =0;
    for (int j = 0; j < 180; j+=90)
    {
        for (int i = 0; i < diagonale-29; i+=30)
        {
	    	int indexk = 0;
		int imax = 0;
		int max = 0;
                for (int k =0 ; k <= 30; k++)
                {
                        if (i+k >= 0 && i+k < diagonale)
                        {
				if( A[i+k][j] >= max)
				{
                            		max = A[i+k][j];
                            		indexk = i+k;
					A[imax][k]=-1;
					imax = i+k;
				}
				else
				{
					A[i+k][j] = -1;
				}
                        }
                }

            if (A[indexk][j] >275)
            {
                    if (j >= 90 && j <= 90)
                    {
                        for (int x = 0; x < width; x++)
                        {
                            int y = (int) (indexk - x * cos(PI*(j)/180.0) / sin(PI*(j)/180.0));
                            Uint32 pix = SDL_MapRGB(image->format, 178, 33, 33);
                            if (y < height && y >= 0)
                            {
				Uint32 pixel = get_pixel(image, floor(x), floor(y));
            			Uint8 r,g,b;
            			SDL_GetRGB(pixel, image->format, &r, &g, &b);

				if(r == 255)
				{
					put_pixel(image,x,y,pix);
				}

                                put_pixel(image, x, y, pix);
				Line +=1;

                            }
                        }
                    }
                    if (j == 0)
                    {
                        for (int y = 0; y < height; y++)
                        {
                            int x = (int) (indexk - y * sin(PI*(j)/180.0) / cos(PI*(j)/180.0));
                            Uint32 pix = SDL_MapRGB(image->format, 178, j, j);
                            if (x < width && x >= 0)
                            {
				Uint32 pixel = get_pixel(image, floor(x), floor(y));
            			Uint8 r,g,b;
            			SDL_GetRGB(pixel, image->format, &r, &g, &b);

				if(r == 255)
				{
					put_pixel(image,x,y,pix);
				}
                                put_pixel(image, x, y, pix);
				Line += 1;
                            }
                        }
                    }
            }
        }
    }
    //printf("%i",Line);
    //SDL_SaveBMP(houghSpace, "output/houghSpace.bmp");
    //SDL_SaveBMP(image, "output/muchachos.bmp");
    //SDL_SaveBMP(intersection, "output/intersection.bmp");
    // squaredetect();
    //SDL_FreeSurface(intersection);
    //SDL_FreeSurface(image);
    //SDL_FreeSurface(houghSpace);
}
int right_corner(SDL_Surface *image,int i,int j){
	int x=i;
	int interx=i;
	while(x<image->w){
		Uint32 pixel_r=get_pixel(image,x,j+1);
		Uint8 r1,g1,b1;
            	SDL_GetRGB(pixel_r, image->format, &r1, &g1, &b1);
		if(r1==255){
			Uint32 pixel_hr=get_pixel(image,x+1,j-1);
			Uint32 pixel_br=get_pixel(image,x+1,j+1);
			Uint32 pixel_bg=get_pixel(image,x-1,j+1);
			Uint32 pixel_hg=get_pixel(image,x-1,j-1);
			int nb_dark=0;
			Uint8 r2,g2,b2;
			Uint8 r3,g3,b3;
			Uint8 r4,g4,b4;
			Uint8 r5,g5,b5;
            		SDL_GetRGB(pixel_hr, image->format, &r2, &g2, &b2);
            		SDL_GetRGB(pixel_br, image->format, &r3, &g3, &b3);
            		SDL_GetRGB(pixel_bg, image->format, &r4, &g4, &b4);
            		SDL_GetRGB(pixel_hg, image->format, &r5, &g5, &b5);
			if(r2==0){
				nb_dark++;
			}
			if(r3==0){
				nb_dark++;
			}
			if(r4==0){
				nb_dark++;
			}
			if(r5==0){
				nb_dark++;
			}
			if(nb_dark>=2){
				break;
			}
			interx=x;
		}
		x++;

	}
	return interx;
}
int bottom_corner(SDL_Surface *image,int i,int j){
	int y=j;
	int intery=j;
	while(y<image->h){
		Uint32 pixel_r=get_pixel(image,i+1,j);
		Uint8 r1,g1,b1;
            	SDL_GetRGB(pixel_r, image->format, &r1, &g1, &b1);
		if(r1==255){
			Uint32 pixel_hr=get_pixel(image,i+1,y-1);
			Uint32 pixel_br=get_pixel(image,i+1,y+1);
			Uint32 pixel_bg=get_pixel(image,i-1,y+1);
			Uint32 pixel_hg=get_pixel(image,i-1,y-1);
			int nb_dark=0;
			Uint8 r2,g2,b2;
			Uint8 r3,g3,b3;
			Uint8 r4,g4,b4;
			Uint8 r5,g5,b5;
            		SDL_GetRGB(pixel_hr, image->format, &r2, &g2, &b2);
            		SDL_GetRGB(pixel_br, image->format, &r3, &g3, &b3);
            		SDL_GetRGB(pixel_bg, image->format, &r4, &g4, &b4);
            		SDL_GetRGB(pixel_hg, image->format, &r5, &g5, &b5);
			if(r2==0){
				nb_dark++;
			}
			if(r3==0){
				nb_dark++;
			}
			if(r4==0){
				nb_dark++;
			}
			if(r5==0){
				nb_dark++;
			}
			if(nb_dark>=2){
				break;
			}
			intery=y;
		
		}
		y++;

	}
	return intery;
}

void detect(SDL_Surface *image){

	int width=image->w;
	int heigth=image->h;
	int max = 0;
	int maxY=0;
	int valx=0;
	int valy=0;
	int lengthx=0;
	int lengthy=0;
	for(int i =0;i<width;i++){
		for(int j=0;j<heigth;j++){
			Uint32 pixel=get_pixel(image,i,j);
			Uint8 r,g,b;
            		SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if(r==255){
				Uint32 pixel_r=get_pixel(image,i+1,j);
				Uint32 pixel_b=get_pixel(image,i,j+1);
				Uint8 r1,g1,b1;
				Uint8 r2,g2,b2;
            			SDL_GetRGB(pixel_r, image->format, &r1, &g1, &b1);
            			SDL_GetRGB(pixel_b, image->format, &r2, &g2, &b2);

				if(r1==255 && r2==255){
					int x1=right_corner(image,i,j);
					lengthx=x1-i;
					int y1=bottom_corner(image,i,j);
					lengthy=y1-j;
					if(abs(lengthy-lengthx)>10){
						continue;
					}
					else{
						if(lengthx>max){
							max=lengthx;
							valx=i;
						}
						if(lengthy>maxY){
							maxY=lengthy;
							valy=j;
						}
					}
				}
				if(r1==255){
					i++;
				}
			}
			else{
				i+=1;
			}
		}
	if(lengthx<lengthy){
		lengthx=lengthy;
	}

	//SDL_Surface* image = loadImage("output/rotate.bmp");
        SDL_Surface* imagedest = SDL_CreateRGBSurface(0,lengthx,lengthx,32,0,0,0,0);
        SDL_Rect leftR = {valx,valy, lengthx, lengthx};
        SDL_BlitSurface(image,&leftR,imagedest,NULL);
        SDL_SaveBMP(imagedest,"final_square.bmp");
        SDL_FreeSurface(imagedest);
        //SDL_FreeSurface(image);
}
}
