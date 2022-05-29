#include <stdio.h>
#include <err.h>

// SDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//Basic usefull functions with SDL

////////////Pixel operations and functions/////////////////
static inline
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
	long h = surface->h;
	long w = surface->w;
	if (x>=w || y>=h)
		return 0;
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
	long h = surface->h;
	long w = surface->w;
	if (x>=w || y>=h)
		return;
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}


/////////SDL operations and functions///////////


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

void wait_for_keydown()
{
	SDL_Event event;

	// Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
	} while(event.type != SDL_KEYUP);
}

// Save and create

void Save_Image(SDL_Surface* img, char *name)
{
	if (SDL_SaveBMP(img, name) != 0)
		printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
	printf("Saving new image as \"%s\" : Done\n",name);
}

void copy_surface(SDL_Surface* img, SDL_Surface* img2)
{
	Uint32 pixel;
	long h = img->h;
	long w = img->w;
	for (size_t i = 0; i < (size_t)w; i++) //x axe
		for (size_t k = 0; k < (size_t)h; k++) //y axe
		{
			pixel = get_pixel(img, i, k);
			put_pixel(img2, i, k, pixel);
		}
}
void Create_image(char *name, long width, long height, int red,                 
                int green, int blue)                                            
{                                                                               
        SDL_Surface* img;                                                       
        img = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);           
        Uint8 r = red;                                                          
        Uint8 g = green;                                                        
        Uint8 b = blue;                                                         
        SDL_FillRect(img, NULL, SDL_MapRGB(img->format, r, g, b));              
        printf("Surface create : Done\n");                                      
        Save_Image(img, name);                                                  
        SDL_FreeSurface(img);                                                   
}                                                                               
                                                                                
void copy(char* path_img, char* path_toCopy)                                    
{                                                                               
        // initialize                                                           
        SDL_Surface* toCopy = load_image(path_toCopy);                          
        Save_Image(toCopy, path_img);                                           
                                                                                
        // free                                                                 
        SDL_FreeSurface(toCopy);                                                
}
