#include <err.h>                                                                
#include "SDL/SDL.h"                                                            
#include "SDL/SDL_image.h"                                                      
#include "image_operations.h"                                                   
//#include "sdl_functions.h"
//#include "image_saving.h"
#include <math.h>
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
/*
void Filter25(SDL_Surface *img, double scale[25])                       
{               
        //height and width                                                      
        int h = img->h;                                                         
        int w = img->w;                                                         
        SDL_Surface *img2 = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);      
        //Some Goode Variables                                                  
        Uint32 pixel;                                                           
        double center;                                                          
        double sum = 0;                                                         
        double div = 0;                                                         
        for (size_t i = 0; i < 25;i++)                                          
                div += scale[i];                                                
       for (size_t i = 0; i < (size_t)w;i++) //x axe                           
       {                                                                       
                for (size_t k =0; k < (size_t)h;k++) //y axe                    
                {                                                               
                        center = Get_gray_color(img, i, k, w, h, 0);            
                        sum = scale[12]*center;                                 
                        //Matrix path                                           
                        for (size_t m = 0; m < 5;m++) //y axe                   
                                for (size_t l = 0; l < 5;l++) //x axe           
                                        if (l != 2 || m != 2)                   
                                                sum = sum+(double)Get_gray_color(img,
                                                                (int)i-2+l, (int)k-2+m,
                                                                w, h, center) * scale[m*5+l];
                                                                                
                        if (div != 0)                                           
                                sum /= div;                                     
                        if (sum > 255)                                          
                                sum = 255;                                      
                        if (sum < 0)                                            
                                sum = 0;                                        
                        pixel = SDL_MapRGB(img2->format, sum, sum, sum);
                        put_pixel(img2, i, k, pixel);
                }
        }
        SDL_FreeSurface(img);
        SDL_Surface *img3 = img2;
	Save_Image(img3,"Images/25.bmp");                          
        Save_Image(img3,"Images/image_result.bpm");                                            


        printf("Chosen filter 5x5 : Done\n");
}

Uint8 Light_Colored_Pixel(SDL_Surface *img)                                     
{                                                                               
        Uint32 pixel;                                                           
        size_t height = img->h;                                                 
        size_t width = img->w;                                                  
        Uint8 r,g,b;                                                            
        Uint8 light = 130;                                                      
        for (size_t i = 0; i < width;i++)                                       
                for (size_t k =0; k < height;k++)                               
                {                                                               
                        pixel = get_pixel(img, i, k);                           
                        SDL_GetRGB(pixel, img->format, &r, &g, &b);             
                        if (r>light)                                            
                                light = r;                                      
                }                                                               
        return light;                                                           
}                                                                               
*/      
Uint32 contrast_p(Uint32 pixel, double fact){
	if(pixel<=255/2)                                        
        pixel=(Uint32)((255/2)*pow((double)2*pixel/255,fact));
        else                                                    
        pixel=255-contrast_p((Uint32)(255-pixel),fact);
	return pixel;


}

void contrast(char *path, int fact){                                     
     SDL_Surface* image_surface;                                                 
     init_sdl();                                                                 
     image_surface = load_image(path);
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
     Save_Image(image_surface,"Images/contrast.bmp");                          
     Save_Image(image_surface,path);                                            
     SDL_FreeSurface(image_surface);
}
void invert(char *path){
	SDL_Surface *image;
	init_sdl();
	image=load_image(path);
	for(int i = 0; i<image->w;i++){                                         
                for(int j = 0; j<image->h;j++){                                 
                        Uint32 pixel = get_pixel(image, i, j);                  
                        Uint8 r, g, b;                                          
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			pixel = SDL_MapRGB(image->format,255-r,255-g,255-b);
			put_pixel(image, i, j, pixel);
		}
	}
     Save_Image(image,"Images/invert.bmp");                          
     Save_Image(image,path);                                            
     SDL_FreeSurface(image);

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

void brightness(char *path){
       SDL_Surface *image;
	init_sdl();
	image=load_image(path);

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
        Save_Image(image,"Images/brightness.bmp");                          
        Save_Image(image,path);                                            
        SDL_FreeSurface(image);
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
void median_filter(char *path){
       SDL_Surface *image;
	init_sdl();
	image=load_image(path);


	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			int *neighbours=get_neighbours_pixel(image,i,j);
			sort_swap(neighbours,9);
			int pixel=median(neighbours);
			put_pixel(image,i,j,(Uint32)pixel);
		}
	}
        Save_Image(image,"Images/median.bmp");                          
        Save_Image(image,path);                                            
        SDL_FreeSurface(image);

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
		if(varBetween>varMax){
			varMax=varBetween;
			treshold=i;
		}
	}
	return treshold;
}

void binarize(char *path){
        SDL_Surface *image;
	init_sdl();
	image=load_image(path);


	int tresh=otsu_tresholding(image);
	float t=(float) tresh*(8.5/10.0);
	int black_p=0;
	int white_p=0;
	for(int i = 0; i<image->w;i++){
		for(int j = 0; j<image->h;j++){
			Uint32 pixel = get_pixel(image, i, j);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			Uint32 bin_p=255;
			if(r<(Uint32)t){
				black_p++;
				bin_p=0;
			}
			else{
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
        Save_Image(image,"Images/binarize.bmp");                          
        Save_Image(image,path);                                            
        SDL_FreeSurface(image);


}
/*
void Black_white_scale(char *path, int low, int high)                     
{
        SDL_Surface *img;
	init_sdl();
	img=load_image(path);


        Uint8 light = Light_Colored_Pixel(img);                                 
        Uint32 pixel;                                                           
        size_t height = img->h;                                                 
        size_t width = img->w;                                                  
        int sum;                                                                
        int stop = 0;                                                           
        low = low*255/light;                                                    
        high = high*255/light;                                                  
        for (size_t i = 0; i < width;i++) //x axe                               
                for (size_t k =0; k < height;k++) //y axe                       
                {                                                               
                        pixel = get_pixel(img, i, k);                           
                        sum = Get_gray_color(img, i, k, width, height, 0);      
                        if(sum > low && sum < high)                             
                        {                                                       
                                 for (size_t m = 0; m < 5 && stop == 0;m++) //y axe
                                         for (size_t l = 0; l < 5 && stop == 0;l++) //x axe
                                                if (l != 2 || m != 2)           
                                                 {                               
                                                        sum = (double)Get_gray_color(img,
                                                                         (int)i-2+l, (int)k-2+m, width, height, 0);
                                                       if (sum > high)         
                                                        {                       
                                                                pixel = SDL_MapRGB(img->format, 255,255,255);
                                                                stop = 1;       
                                                        }                       
                                                 }                               
                                 if (stop == 0)                                  
                                         pixel = SDL_MapRGB(img->format,0,0,0);  
                         }
                         if (sum > high)                                         
                                 pixel = SDL_MapRGB(img->format,255,255,255);    
                         else if (sum < low)                                     
                                 pixel = SDL_MapRGB(img->format,0,0,0);          
                        put_pixel(img, i, k, pixel);                            
                        stop = 0;                                               
                }
	Save_Image(img,"Images/bw.bmp");                          
        Save_Image(img,path);                                            
        SDL_FreeSurface(img);

                                                              
         printf("Black or white filter : Done\n");                               
}  


char More_dark(char *path)                                                      
{                                                                               
        SDL_Surface* img = load_image(path);                                    
        Uint32 pixel;                                                           
        size_t height = img->h;                                                 
        size_t width = img->w;                                                  
        Uint8 g;                                                                
        int dark = 0;                                                           
        int light  = 0;                                                         
        for (size_t i = 0; i < width;i++)                                       
                 for (size_t k =0; k < height;k++)                               
                 {                                                               
                         g = Get_gray_color(img, i, k, width, height, 0);        
                         if (g == 255)                                           
                                 light += 1;                                     
                         else                                                    
                                dark += 1;                                      
                         pixel = SDL_MapRGB(img->format, g,g,g);                 
                         put_pixel(img, i, k, pixel);                            
                 }                                                               
        if (dark > light+100000)                                                
                return 1;                                                       
        return 0;                                                               
} */
