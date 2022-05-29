#ifndef PRETRATMENT_COLOR_H
#define PRETRATMENT_COLOR_H
//void Filter25(SDL_Surface *img, double scale[25]);   
//char More_dark(char *path);
//void Black_white_scale(char *path, int low, int high);
void sort_swap(int *array,int size);
int* get_neighbours_pixel(SDL_Surface *image,int i,int j);
void invert(char *path);
void contrast(char *path, int fact);
float color_max(SDL_Surface *image);
void brightness(char *path);
int median(int *array);
int ave(int*array);
void median_filter(char *path);
void aver_filter(SDL_Surface *image);
int otsu_tresholding(SDL_Surface *image);
void binarize(char *path);
#endif
