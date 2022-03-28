#ifndef SEGMENTATION_H
#define SEGMENTATION_H

typedef struct Line_t
{
    void *x1;
    void *y1;
    void *x2;
    void *y2;
    struct Line_t *next;
    struct Line_t *prev;
} Line;
typedef struct
{
    Line *head;
    Line *tail;
    size_t length;
} MyList;


void initializeMyList(MyList *list);
void append(MyList *list, Line *ligne);
void hough_transform(SDL_Surface *image);
Line *initLine(void *x1,void *y1,void *x2, void *y2);

#endif
