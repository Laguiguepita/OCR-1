#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdl_functions.h"

#include "pixel_operations.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"


#define PI 3.14159265358979

void hough_transform(SDL_Surface *image){
	int width=image->w;
	int height=image->h;
	SDL_Surface *copy_image=image;
	double diagonal=sqrt(width*width+height*height);
	double rho=1.0;
	double theta=1.0;
	double Ntheta=180.0;
	double Nrho=sqrt(diagonal);
	double Dtheta=PI/Ntheta;
	double Drho=sqrt(diagonal)/Nrho;

	double accum[(int)Ntheta][(int)Nrho];
	
	for(int i = 0; i<Ntheta;i++)
        	for (int j =0 ; j<Nrho ;j++)
            		accum[i][j]=0.;
	
	
	
	

	for(int i =0;i<width;i++){
		for(int j=0;j<height;j++){
			if(get_pixel(image, i, j) != 0){
				for(int i_theta=0;i<Ntheta;i++){
					theta=i_theta*Dtheta;
					rho=i*cos(theta)+(width-i)*sin(theta);
					int i_rho=rho/Drho;

					if(i_rho>0 && i_rho<Nrho){
						accum[i_theta][i_rho]+=1;
					}
				}
			}
		}
	}

	int seuil=130;

	double accum_seuil[(int)Ntheta][(int)Nrho];
	for(int i=0; i < Ntheta; i++)
      		for (int j=0; j < Nrho; j++)
        		accum_seuil[i][j] = accum[i][j];
	//retiens les valeurs de l'accumulateur en dessous d'un seuil
	for(int i_theta=0;i_theta<Ntheta;i_theta++){
		for(int i_rho=0;i_rho<Nrho;i_rho++){
			if(accum[i_theta][i_rho]<seuil){
				accum_seuil[i_theta][i_rho] += 1;

				}
		}
	}
	int taille=0;
	//compte le nombres de points a stocker

	for(int i_theta=0;i_theta<Ntheta;i_theta++){
                for(int i_rho=0;i_rho<Nrho;i_rho++){

                         if(accum_seuil[i_theta][i_rho]!=0){
                                taille++;
                                }
                }
        }
	//rempli tableau 2 dim de zero
	double lignes[taille][2];

	for(int i = 0; i<taille;i++)
                for (int j =0 ; j<2 ;j++)
						lignes[i][j]=0.;
	int t=0;
	//recup l'ensemble des lignes a tracer
	for(int i_theta=0;i_theta<Ntheta;i_theta++){
                for(int i_rho=0;i_rho<Nrho;i_rho++){

                         if(accum_seuil[i_theta][i_rho]!=0){
				lignes[t][0]=i_rho*Drho;
				lignes[t][1]=i_theta*Dtheta;
				t++;
			 }
		}
	}

	uint8_t red = SDL_MapRGB(image->format,0xFF,0x00,0x00);
	for(int i=0;i<taille;i++){
		rho=lignes[i][0];
		theta=lignes[i][1];
		int a=cos(theta);
		int b=sin(theta);
		int x0=a*rho;
		int y0=b*rho;
		int x1=(x0+1000*(-b));
		int y1=(y0+1000*a);
		int x2=(x0-1000*(-b));
		int y2=(y0-1000*a);

		draw_line(copy_image,x1,y1,x2,y2,red);
	}
	

}

