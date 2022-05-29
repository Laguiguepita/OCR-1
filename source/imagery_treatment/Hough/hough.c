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
void houghTransformation(char *path)
{
    SDL_Surface *image;
    init_sdl();
    image=load_image(path);
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
                            Uint32 pix = SDL_MapRGB(image->format, 255, 33, 33);
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
                            Uint32 pix = SDL_MapRGB(image->format, 255, j, j);
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
    SDL_SaveBMP(image,path);
}
int* right_corner(SDL_Surface *image,int i,int j,int height,int* length){
		
	int* result = malloc(sizeof(int) *100000);
	for(int e = height - 1; e > j; e--)
	{
	    Uint32 pixel = get_pixel(image, i, e);
            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            
		if(r == 255)
		{
			*(result + *length) = e - j;
			*length += 1;
		}

	}
	return result;
}
int* bottom_corner(SDL_Surface *image,int i,int j,int* length,int width){
{	
	int* result = malloc(sizeof(int) * 100000);
	for(int e = width - 1; e > i; e--)
	{
		Uint32 pixel = get_pixel(image, e, j);
		Uint8 r,g,b;
            	SDL_GetRGB(pixel, image->format, &r, &g, &b);
            
		if(r == 255)
		{
			*(result + *length) = e - i;
			*length += 1;
		}

	}
	return result;
}

}
int maxLength(int* verticalLengths, int* horizontalLengths, int vL,int hL)
{
	int e = 0;
	int e2 = 0;
	int maxlength = 0;
	while(e < vL)
	{
		while(e2 < hL)
		{
			if((*(verticalLengths+e))+20 >= *(horizontalLengths+e2) && (*(verticalLengths+e))-20 <= *(horizontalLengths+e2))
			{
				int vLength = *(verticalLengths+e);
				if(maxlength < vLength)
				{
					maxlength=(vLength);
				}
			}
			e2+=1;
		}
		e2 =0;
		e +=1;
	}
	return maxlength;
}

void detect(SDL_Surface *image){

	int heigth=image->h;
	int width =image->w;
	int valx=0;
	int valy=0;
	int length = 0;
	//int length3 =0;
	//int valx2 =0;
	//int valy2 =0;
	for(int i =350;i<width/2;i++){
		for(int j =170 ; j<heigth/2;j++){
			Uint32 pixel=get_pixel(image,i,j);
			Uint8 r,g,b;
            		SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if(r==255)
			{
				int verti=0;
				int hori=0;
				int* vertical = bottom_corner(image,i,j,&verti,width);
				int* horizontal = right_corner(image,i,j,heigth,&hori);
				int max = maxLength((vertical),(horizontal),verti,hori);
				if(max!=0){
					int cordx=i;
					int cordy=j;
					int length2=max;
					if(length2>length)
					{
						valx=cordx;
						valy=cordy;
						length=length2;
					}
			}
				free(vertical);
				free(horizontal);

			}

		}
	
	}
	/*
	for(int i =width-1;i<width/2;i--){
		for(int j =heigth-1 ; j<heigth/2;j--){
			Uint32 pixel=get_pixel(image,i,j);
			Uint8 r,g,b;
            		SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if(r==255)
			{
				int verti2=0;
				int hori2=0;
				int* vertical2 = bottom_corner(image,i,valy,&verti2,j);
				int* horizontal2 = right_corner(image,valx,j,i,&hori2);
				int max2 = maxLength((vertical2),(horizontal2),verti2,hori2);
				if(max2!=0){
					int cordx2=i;
					int cordy2=j;
					int length4=max2;
					if(length4>length3)
					{
						valx2=cordx2;
						valy2=cordy2;
						length3=length4;
					}
			}
				free(vertical2);
				free(horizontal2);

			}

		}
	
	}
	if (length3<length){
	length = valx2;
	}*/


	
        SDL_Surface* imagedest = SDL_CreateRGBSurface(0,length,length,32,0,0,0,0);
	for(int x1=0;x1<length;x1++){
		for(int x2=0;x2<length;x2++){
			Uint32 pixel= get_pixel(image,valx+x1,valy+x2);
			put_pixel(imagedest,x1,x2,pixel);
		}
	}
	printf("%d,%d,%d\n",valx,valy,length);
        SDL_SaveBMP(imagedest,"final_square.bmp");
	
	
			
}	

	//SDL_Surface* image = loadImage("output/rotate.bmp");
        //SDL_Surface* imagedest = SDL_CreateRGBSurface(0,lengthx,lengthx,32,0,0,0,0);
        //SDL_Rect leftR = {valx,valy, lengthx, lengthx};
        //SDL_BlitSurface(image,&leftR,imagedest,NULL);
        //SDL_SaveBMP(imagedest,"final_square.bmp");
	//SDL_Surface *image2=SDL_LoadBMP("final_square.bmp");
        //IMG_SavePNG(image2,"final_square.png");
	//SDL_FreeSurface(imagedest);
        //SDL_FreeSurface(image);

//	return image2;

//	SDL_FreeSurface(image2);
				/*else if(r1==255 && r2!=255){
					Uint32 pixell=get_pixel(image,i,j+1);
					Uint8 rr,gg,bb;
					SDL_GetRGB(pixell, image->format, &rr, &gg, &bb);
					int sav=i;
					while(rr!=255){
						Uint32 pix=get_pixel(image,i,j+1);
						Uint8 re,gb,bg;
						SDL_GetRGB(pix, image->format, &re, &gb, &bg);
						if(re==255){
							rr=255;
						}
						i++;
					}
					int x1=right_corner(image,i,j);
					lengthx=x1-i;
					int y1=bottom_corner(image,i,j);
					lengthy=y1-j;
					if(abs(lengthy-lengthx)<20){
						if(lengthx>max){
							max=lengthx;
							valx=i;
						}
						if(lengthy>maxY){
							maxY=lengthy;
							valy=j;
						}
					}
					else{
						i=sav;
						i++;
					}
				
				}
				else if(r2==255 && r1!=255){
					//Uint32 pixeel=get_pixel(image,i+1,j);
					//Uint8 rz,gz,bz;
					//SDL_GetRGB(pixeel, image->format, &rz, &gz, &bz);
					//while(rz!=255){
					//	Uint32 px=get_pixel(image,i+1,j);
					//	Uint8 ra,ga,ba;
					//	SDL_GetRGB(px, image->format, &ra, &ga, &ba);
					//	if(ra==255){
					//		rz=255;
					//	}
					//	j++;

					
				}*/


			
			
			//else{
	
