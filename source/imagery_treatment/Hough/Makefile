# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl SDL_image SDL_gfx` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -lm -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image SDL_gfx` 

all: main
segmentation.o: sdl_functions.h pixel_operations.h
hough.o:sdl_functions.h pixel_operations.h
segmentation:segmentation.o sdl_functions.o pixel_operations.o 
main:segmentation.o hough.o sdl_functions.o pixel_operations.o 

clean:
	${RM} *.o
	${RM} *.d

# END
