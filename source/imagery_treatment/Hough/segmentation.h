#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include "../Pretreatment/image_operations.h"
typedef struct Line_t
{
    int *x1;
    int *y1;
    int *x2;
    int *y2;
    struct Line_t *next;
    struct Line_t *prev;
} Line;

typedef struct
{
    Line *head;
    Line *tail;
    size_t length;
} List;


List *initList();
void append(List *list, Line *ligne);
List *hough_transform(SDL_Surface *image);
Line *initLine(int *x1,int *y1,int *x2, int *y2);
void Line_sort(List *list,int max);
void detect2(char path[]);
int isTache(SDL_Surface *img);
void resize(char path[]);
//void split(char path[]);



#endif
