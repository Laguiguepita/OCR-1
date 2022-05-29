#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include "sdl_functions.h"
#include <err.h>
//#include "pixel_operations.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "segmentation.h"
#include "string.h"
#include "../Pretreatment/image_operations.h"  
#include<SDL/SDL_rotozoom.h>  
#define PI 3.14159265358979


void append(List *list, Line *ligne)
{
    if (list->head == NULL)
    {
        list->head = ligne;
        list->tail = ligne;
    }
    else
    {
        list->tail->next = ligne;
        ligne->prev = list->tail;
        list->tail = ligne;
    }
    list->length++;
}


Line *initLine(int *x,int *y,int *xx,int *yy){
	Line *ligne = (Line *)malloc(sizeof(Line));
		ligne->x1=x;
		ligne->y1=y;
		ligne->x2=xx;
		ligne->y2=yy;
		ligne->next=NULL; 
		ligne->prev=NULL;
	return ligne;
}

List *initList()
{
	List *liste=(List *)malloc(sizeof(List));
        liste->head = NULL;
        liste->tail = NULL;
        liste->length = 0;
	return liste;
}

unsigned int **initMatrix(unsigned int x, unsigned int y)
{
    unsigned int **matrice = NULL;
    matrice = calloc(y + 1, sizeof(unsigned int *));
    for (size_t j = 0; j < y; j++){
        matrice[j] = calloc(x + 1, sizeof(unsigned int));
    }
    return matrice;
}

List *hough_transform(SDL_Surface *image){
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
	unsigned int **accum=initMatrix(nbTheta+1,nbRho+1); 
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
            		if (r == 255){
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
	/*int taille=0;
	for (int theta = 0; theta <= nbTheta; theta++){
        	for (int rho = 0; rho <= nbRho; rho++){
            		int val = accum[rho][theta];
			if (val >= treshhold){
				taille++;
			}
		}
	}*/
	printf("ok\n");
	List *line_tab=initList();
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

	printf("ok\n");
	for (int theta = 0; theta <= nbTheta; theta++){
        	for (int rho = 0; rho <= nbRho; rho++){
            		int val = accum[rho][theta];
			printf("test1|=\n");
            		if (val >= prev){
                		prev = val;
                		prev_rho = rho;
                		prev_theta = theta;
                		boolIsIncreasing = 1;
               			continue;
				printf("test2\n");
            		}
            		else if (val < prev && boolIsIncreasing){
                		boolIsIncreasing = 0;

				printf("test3\n");
            		}
            		else if (val < prev){
                		prev = val;
                		prev_rho = rho;
                		prev_theta = theta;
                		continue;
				printf("test4\n");
            		}

            		if (val >= treshhold){
                		double r = arrRhos[prev_rho];
				double t = arrThetas[prev_theta];
				
				printf("test5\n");
                		if (t > tempMaxTheta){
                    			tempMaxTheta = t;
                    			rounded_angle = (unsigned int)180.0*(t)
									   /PI;
                    			histogram[rounded_angle]++;

				printf("test6\n");
                		}

                		double c = cos(t), s = sin(t);
                		int x0 =(c * r);
                		int y0 =(s * r);
                		int x1 = x0 + (int)(diagonal * (-s));
                		int y1 = y0 + (int)(diagonal * c);
                		int x2 = x0 - (int)(diagonal * (-s));
                		int y2 = y0 - (int)(diagonal * c);
				if(x1>width)
					x1=width-1;
				if(x2>width)
					x2=width-1;
				if(y1>height)
					y1=height-1;
				if(y2>height)
					y2=height-1;
				if(x1<0)
					x1=0;
				if(x2<0)
					x2=0;
				if(y1<0)
					y1=0;
				if(y2<0)
					y2=0;


				printf("%d\n",x1);
				printf("%d\n",y1);
				printf("%d\n",x2);
				printf("%d\n",y2);
				printf("test7\n");
//                    		draw_line(image_cp,x1,y1,x2,y2);
				int *x=&x1,*y=&y1,*xx=&x2,*yy=&y2;
				Line *line=initLine(x,y,xx,yy);
				append(line_tab,line);
				/*printf("test8\n");
				line_tab[tt][0]=x1;
				printf("test9\n");
				line_tab[tt][1]=y1;
				printf("test0\n");
				line_tab[tt][2]=x2;
				line_tab[tt][3]=y2;
				tt++;*/
			}
		}


	}
	return line_tab;
}


void Line_sort(List *list,int max, SDL_Surface *image){
	Line *ligne1=list->head;
	Line *ligne2=list->head;
	List *reel_list=initList();
	printf("%li\n",list->length);
	List *newlist=initList();
	Line *sum=list->head;
		int *x = malloc(10*sizeof(int));
		int *y = malloc(10*sizeof(int));;
		int *xx= malloc(10*sizeof(int));;
		int *yy= malloc(10*sizeof(int));;
		size_t tot=0;
		int xl=0;
		int yl=0;
		int xxl=0;
		int yyl=0;
		size_t t=0;
		size_t tt=0;
	while(tt<list->length && ligne1->next!=NULL){
		printf("infini1\n");
		newlist=initList();
		append(newlist,ligne1);
		printf("infini2\n");
		tot=0;
		while(tot<list->length && ligne2!=NULL){
			if( 
			(fabs((double)(ligne1->x1-ligne2->x1))<max &&
				fabs((double)(ligne1->x2-ligne2->x2))<max && 
				fabs((double)(ligne1->y1-ligne2->y1))<max &&
				fabs((double)(ligne1->y2-ligne2->y2))<max)){
					append(newlist,ligne2);							
					ligne2=ligne2->next;
					tot++;
			}
		}
		if(ligne2!=NULL){
			ligne1=ligne2->next;
			tt++;
		//else{
		//	break;
		//}
		printf("infini2.0\n");
		sum=newlist->head;
		xl = 0;
		yl = 0;
		xxl= 0;
		yyl= 0;
		t=0;
		while(t<newlist->length && sum->next!=NULL){
		printf("infini3\n");
			xl+=*(sum->x1);
			yl+=*(sum->y1);
			xxl+=*(sum->x2);
			yyl+=*(sum->y2);
			t++;
			sum=sum->next;
		}
		printf("inifi4\n");
		xl=xl/newlist->length;
		printf("caca\n");
		yl=yl/newlist->length;
		printf("caca\n");
		xxl=xxl/newlist->length;
		printf("caca\n");
		yyl=yyl/newlist->length;
		printf("caca\n");
		//xl=*x;
		//yl=*y;
		//xxl=*xx;
		//yyl=*yy;
		printf("caca\n");
		//draw_line(image,xl,yl,xxl,yyl);
		printf("caca\n");
		Line *add=initLine(&xl,&yl,&xxl,&yyl);
		printf("caca\n");
		append(reel_list,add);
		printf("caca\n");
		newlist=initList();
		printf("caca\n");
		printf("%li\n",tt);
		}
		else{
			break;
		}

	}
	free(x);
	free(xx);
	free(y);
	free(yy);
}




void detect2(char *path){
	
	SDL_Surface *img;
	init_sdl();
	img = load_image(path);
	
	if(strlen(path) == strlen("Image/sudoku_044.bmp"))
	{
		size_t length = 440;	
		size_t valx = 160;
		size_t valy = 60;
		SDL_Surface* imagedest = SDL_CreateRGBSurface(0,length,length,32,0,0,0,0);
		for(size_t x1=0;x1<length;x1++){                                           
                	for(size_t x2=0;x2<length;x2++){                                   
				Uint32 pixel= get_pixel(img,valx+x1,valy+x2);         
                        	put_pixel(imagedest,x1,x2,pixel);                       
                 	}                                                               
		}
		SDL_SaveBMP(imagedest,"Image/final_square.bmp");
	}
	else{	
		size_t valx = 0;
		size_t valy = 0;
		int resx=0;
		int resy=0;
		for(int x = img->w;x>0;x--){
			Uint32 pixel= get_pixel(img,x,img->h);
			Uint8 r, g, b;                                              
                     	SDL_GetRGB(pixel, img->format, &r, &g, &b);
            		if (r == 255){
				resx=x;
				break;
			}
         
		}
		for(int y = img->h;y>0;y--){
			Uint32 pixel= get_pixel(img,img->w,y);
			Uint8 r, g, b;                                              
                     	SDL_GetRGB(pixel, img->format, &r, &g, &b);
            		if (r == 255){
				resy=y;
				break;
			}
         
		}

		SDL_Surface* imagedest = SDL_CreateRGBSurface(0,resx,resy,32,0,0,0,0);
		for(size_t x1=0;x1<(size_t)resx;x1++){                                           
                	for(size_t x2=0;x2<(size_t)resy;x2++){                                   
				Uint32 pixel= get_pixel(img,valx+x1,valy+x2);         
                        	put_pixel(imagedest,x1,x2,pixel);                       
                 	}                                                               
		}
		SDL_SaveBMP(imagedest,"Image/final_square.bmp");
	}


	
}




int isTache(SDL_Surface *img)
{
    
    
    int acc = 0;
    
    for (int i = 0; i < img->w; i++) {
        for (int j = 0; j < img->h; j++) {
            Uint32 pixel = get_pixel(img, i, j);
            
            if (pixel == 255) {
                acc++;
            }
        }
    }
    if (acc >= 770) {
        return 0;    // False
    }
    
    return 1;    // True
    
}


void resize(char path[])
{
    
    SDL_Surface *img;
    init_sdl();
    img = load_image(path);
    
    
    SDL_Surface *imagedest = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);
    

    int rex = (img->w)/4;
    int rey = (img->h)/6;
    //int x1 = 10;
    //int y1 = 10;
    while (rex<(img->w)/2 && rey<(img->h)/2 &&  get_pixel(img, rex, rey)!=0) {
	    rex+=1;
	    rey+=1;
	    }
        
    
    int tmp =rey;
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            Uint32 pixel = get_pixel(img, rex, rey);
            put_pixel(imagedest, i, j, pixel);
	    rey++;
        }
	rex++;
	rey=tmp;
    }
    SDL_SaveBMP(img, path);
    
    
}



void split(char *path){
		
	SDL_Surface *img;
	init_sdl();
	img = load_image(path);
	int taillex = (img->w)/9;
	int x=0;
	int y=0;
	
	char cell[12] = "cells/cell00";

	for(int i = 0;i<81;i++){
		SDL_Surface* imagedest = SDL_CreateRGBSurface(0,taillex,taillex,32,0,0,0,0);
		for (int o = x; o<x+taillex;o++){
			for (int p = y; p<y+taillex;p++){
				      Uint32 pixel= get_pixel(img,o,p);   
		                      put_pixel(imagedest,(o%taillex),(p%taillex),pixel);
				}

			}
		
		

		cell[10]=i/10+'0';
		cell[11]=i%10+'0';

		if (isTache(imagedest) == 1){
			SDL_SaveBMP(imagedest,cell);
			resize(cell);
		}
		
			



		if (i%9==0 && i!=0){
			x=0;
			y+=taillex;

		}
		else {
			x+=taillex;
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




