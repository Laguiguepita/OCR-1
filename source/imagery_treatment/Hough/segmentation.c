#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdl_functions.h"
#include <err.h>
#include "pixel_operations.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"


#define PI 3.14159265358979
unsigned int **initMatrice(unsigned int x, unsigned int y)
{
    unsigned int **matrice = NULL;
    matrice = calloc(y + 1, sizeof(unsigned int *));
    if (matrice == NULL)
    {
        errx(1, "Memory error");
    }
    for (size_t j = 0; j < y; j++)
    {
        matrice[j] = calloc(x + 1, sizeof(unsigned int));
        if (matrice[j] == NULL)
        {
            errx(1, "Memory error");
        }
    }
    return matrice;
}

void hough_transform(SDL_Surface *image){
	int width=image->w;
	int height=image->h;
	//SDL_Surface *copy_image=image;
	double diagonal=sqrt(width*width+height*height);
	/*double rho=1.0;
	double theta=1.0;
	double Ntheta=180.0;
	double Nrho=round(sqrt(diagonal));
	double Dtheta=PI/Ntheta;
	double Drho=round(sqrt(diagonal))/Nrho;*/
	
	const double maxTheta = 180.0, minTheta = 0.0;
        const double maxRho = diagonal, minRho = -diagonal;
        double nbRho = 2 * diagonal;
	double nbTheta = nbRho;
	
	double rhoStep = (maxRho - minRho) / nbRho;
        double arrRhos[(int)nbRho + 1];
        int i = 0;
	
	/*for(int i = 0; i<Ntheta;i++)
        	for (int j =0 ; j<Nrho ;j++)
            		accum[i][j]=0.;
	*/
        for (double val = minRho; val <= maxRho && i < nbTheta; 
	val += rhoStep, i++)
    	{
        	arrRhos[i] = val;
    	}	
	printf("ok\n");
	double step = (maxTheta - minTheta) / nbTheta;
    	double arrThetas[(int)nbTheta + 1];
    	i = 0;
    	for (double val = minTheta; val <= maxTheta && i < nbTheta;
         val += step, i++)
    	{
        	arrThetas[i] = val;
    	}

	printf("ok\n");
	double cos_tab[(int)nbTheta + 1];
    	double sin_tab[(int)nbTheta + 1];
    	for (int theta = 0; theta < nbTheta+1; theta++)
    	{
        	arrThetas[theta] = PI*arrThetas[theta]/180.0;
        	cos_tab[theta] = cos(arrThetas[theta]);
        	sin_tab[theta] = sin(arrThetas[theta]);
    	}
	
	printf("ok,%f,%d\n",nbTheta+1,(int)nbTheta+1);
	unsigned int **accum=initMatrice(nbTheta+1,nbRho+1); 
    	//unsigned int accum[(size_t)nbTheta+1][(size_t)(nbRho+1)];
	//memset(accum,0,(nbTheta+1)*(nbRho+1)*sizeof(unsigned int)); 
	/*for(int p = 0; p<3000;p++){
        	for (int z =0 ; z<3000;z++){
            		accum[p][z]=0;
		}
	}*/

	printf("ok\n");
	unsigned int max = 0;
    	double rho;
    	int croppedRho;
    	for (int x = 0; x < width; x++){
        	for (int y = 0; y < height; y++){
			Uint32 pixel = get_pixel(image, x, y);              
                     	Uint8 r, g, b;                                              
                     	SDL_GetRGB(pixel, image->format, &r, &g, &b);
            		if (r == 0){
                		for (int theta = 0; theta <= nbTheta; theta++){
                    			rho = x * cos_tab[theta] + 
					y * sin_tab[theta];
                    			croppedRho = rho + diagonal;
                    			accum[croppedRho][theta]++;
                    			if(accum[croppedRho][theta]>max){
                        		max=accum[croppedRho][theta];
                    			}
                		}
            		}
        	}
    	}

	printf("ok\n");
	int treshhold=0.4*max;
	int taille=0;
	for (int theta = 0; theta <= nbTheta; theta++){
        	for (int rho = 0; rho <= nbRho; rho++){
            		int val = accum[rho][theta];
			if (val >= treshhold){
				taille++;
			}
		}
	}
	printf("ok\n");
	unsigned int **line_tab=initMatrice((unsigned int)taille+1,(unsigned int)4+1);
	/*for(int i =0;i<taille;i++){
		for(int j=0;j<4;j++){
			line_tab[i][j]=0;
		}
	}*/
	printf("ok\n");
	int histogram[181];
	for(int i = 0;i<181;i++){
		histogram[i]=0;
	}
	printf("ok\n");

	double tempMaxTheta = 0.0;
	unsigned int rounded_angle;

    	int prev = accum[0][0];
    	int prev_theta = 0, prev_rho = 0;
    	int boolIsIncreasing = 1;
	int tt = 0;
	line_tab[tt][0]++;
	line_tab[tt][0]--;

	printf("ok\n");
	for (int theta = 0; theta <= nbTheta; theta++){
        	for (int rho = 0; rho <= nbRho; rho++){
            		int val = accum[rho][theta];

            		if (val >= prev){
                		prev = val;
                		prev_rho = rho;
                		prev_theta = theta;
                		boolIsIncreasing = 1;
               			continue;
            		}
            		else if (val < prev && boolIsIncreasing){
                		boolIsIncreasing = 0;
            		}
            		else if (val < prev){
                		prev = val;
                		prev_rho = rho;
                		prev_theta = theta;
                		continue;
            		}

            		if (val >= treshhold){
                		double r = arrRhos[prev_rho];
				double t = arrThetas[prev_theta];
			
                		if (t > tempMaxTheta){
                    			tempMaxTheta = t;
                    			rounded_angle = (unsigned int)180.0*(t)
									   /PI;
                    			histogram[rounded_angle]++;
                		}

                		double c = cos(t), s = sin(t);
                		int x0 =(c * r);
                		int y0 =(s * r);
                		int x1 = x0 + (diagonal * (-s));
                		int y1 = y0 + (diagonal * c);
                		int x2 = x0 - (diagonal * (-s));
                		int y2 = y0 - (diagonal * c);

                    		draw_line(image,x1,y1,x2,y2);
				line_tab[tt][0]=x1;
				line_tab[tt][1]=y1;
				line_tab[tt][2]=x2;
				line_tab[tt][3]=y2;
				tt++;
			}
		}


	}
}







	/*
	for(int i =0;i<width;i++){
		for(int j=0;j<height;j++){
			if(get_pixel(image, i, j) != 0){
				for(int i_theta=0;i_theta<Ntheta;i_theta++){
					theta=i_theta*Dtheta;
					rho=i*cos(theta*PI/180.0)+
					(width-j)*sin(theta*PI/180.0);
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
				accum_seuil[i_theta][i_rho] = 0;

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
	double list_rho[taille];
	double list_theta[taille];
	int x=0;
	for(int i_theta=0;i_theta<Ntheta;i_theta++){
                for(int i_rho=0;i_rho<Nrho;i_rho++){
                         if(accum_seuil[i_theta][i_rho]!=0){
				list_rho[x]=i_rho*Drho;
				list_theta[x]=i_theta*Dtheta;
				x++;
			 }
		}
	}
        */ 
	//rempli tableau 2 dim de zero
	/*double lignes[taille][2];

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
*/

	//Uint32 red = SDL_MapRGB(image->format,255,0,0);
	/*for(int i=0;i<taille;i++){
		//printf("%f,%f\n",lignes[t][0],lignes[t][1]);
		rho=list_rho[i];
		theta=list_theta[i];
		double a=cos(theta*PI/180.0);
		double b=sin(theta*PI/180.0);
		double x0=a*(rho*PI/180.0);
		double y0=b*(rho*PI/180.0);
		double x1=fabs(x0+1000*(-b));
		double y1=fabs(y0+1000*a);
		double x2=fabs(x0-1000*(-b));
		double y2=fabs(y0-1000*a);
		printf("%f,%f,%f,%f\n",round(x1),round(y1),round(x2),round(y2));

		draw_line(image,(int)round(x1),(int)round(y1),(int)round(x2),
		(int)round(y2));
	}
	*/




