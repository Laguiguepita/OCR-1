#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdl_functions.h"

#define PI 3.14159265358979

int **hought_transform(SDL_Surface *image){
	int width=image->w;
	int height=image->h;
	SDL_Surface *copy_image=*image;
	double diagonal=sqrt(width*width+height*height);
	double rho=1.0;
	double theta=1.0;
	double Ntheta=180.0;
	double Nrho=sqrt(diagonal);
	double Dtheta=PI/Ntheta;
	double Drho=sqrt(diagonal)/Nrho;
	double accum[Ntheta][Nrho];
	
	for(double i = 0; i<Ntheta;i++)
        	for (double j =0 ; j<Nrho ;j++)
            		accum[i][j]=0.;

	for(int i =0;i<width;i++){
		for(int j=0;j<heigth;j++){
			if(array[i][j]!=0){
				for(i_theta=0;i<Ntheta;i++){
					theta=i_theta*Dtheta;
					rho=i*cos(theta)+(width-i)*sin(theta);
					i_rho=rho/Drho;
					if(i_rho>0 && i_rho<Nrho){
						accum[i_theta][i_rho]+=1;
					}
				}
			}
		}
	}

	int seuil=130;
	double accum_seuil[Ntheta][Nrho];
	for(double i=0; i < Ntheta; i++)
      		for (double j=0; j < Nrho; j++)
        		accum_seuil[i][j] = accum[i][j];
	//retiens les valeurs de l'accumulateur en dessous d'un seuil
	for(i_theta=0;i_theta<Ntheta;i_theta++){
		for(i_rho=0;i_rho<Nrho;i_rho++){
			if(accum[i_theta][i_rho]<seuil){
				accum_seuil[i_theta][i_rho];
				}
		}
	}
	int taille=0;
	//compte le nombres de points a stocker
	for(i_theta=0;i_theta<Ntheta;i_theta++){
                for(i_rho=0;i_rho<Nrho;i_rho++){
                         if(accum_seuil[i_theta][i_rho]!=0){
                                taille++;
                                }
                }
        }
	//rempli tableau 2 dim de zero
	double lignes[taille][2];
	for(double i = 0; i<taille;i++)
                for (double j =0 ; j<2 ;j++)
			matrix[i][j]=0.;
	int t=0;
	//recup l'ensemble des lignes a tracer
	for(i_theta=0;i_theta<Ntheta;i_theta++){
                for(i_rho=0;i_rho<Nrho;i_rho++){
                         if(accum_seuil[i_theta][i_rho]!=0){
				lignes[t][0]=i_rho*Drho;
				lignes[t][1]=i_theta*Dtheta;
				t++;
			 }
		}
	}
	Uint32 red=SDL_MapRGB(image->format,0xFF,0x00,0x00);
	for(int i=0;i<taille;i++){
		rho=lignes[i][0];
		theta=lignes[i][1];
		a=cos(theta);
		b=sin(theta);
		x0=a*rho;
		y0=b*rho;
		x1=(x0+1000*(-b));
		y1=(y0+1000*a);
		x2=(x0-1000*(-b));
		y2=(y0-1000*a);
		draw_line(copy_image,x1,y1,x2,y2,red);
	}
	

}

