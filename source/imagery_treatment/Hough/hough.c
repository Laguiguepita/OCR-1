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
