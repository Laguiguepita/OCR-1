#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void SDL_FreeSurface(SDL_Surface *surface);
void draw_pixel(SDL_Surface *surface, int x, int y, Uint32 color) {
        // 32bpp pixel address
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
        // assign color
        *(Uint32 *)p = color;
}


void swap(int *i, int *j) {
        int t = *i;
        *i = *j;
        *j = t;
}
void draw_line(SDL_Surface *surface,int x1,int y1,int x2,int y2, Uint32 color)
{
        // bresenham line
        steep = fabs(y2 - y1) > fabs(x2 - x1),
        inc = -1;

        if (steep) {
                swap(&x1, &y1);
                swap(&x2, &y2);
        }

        if (x1 > x2) {
                swap(&x1,&x2);
                swap(&y1,&y2);
        }

        if (y1 < y2) {
                inc = 1;
        }

        int dx = fabs(x2 - x1),
            dy = fabs(y2 - y1),
            y = y1, x = x1,
            e = 0;

        for (x; x <= x2; x++) {
                if (steep) {
                        draw_pixel(surface, y, x, color);
                } else {
                        draw_pixel(surface, x, y, color);
                }

                if ((e + dy) << 1 < dx) {
                        e = e + dy;
                } else {
                        y += inc;
                        e = e + dy - dx;
                }
        }
}
