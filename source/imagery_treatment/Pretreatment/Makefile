# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -lm -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image SDL_gfx`

all: display grayscale

display: display.o
grayscale: pixel_operations.o grayscale.o
grayscale.o: pixel_operations.h sdl_functions.h
main:grayscale.o pretreatment_color.o pixel_operations.o sdl_functions.o ../Hough/segmentation.o ../Hough/hough.o 
clean:
	${RM} *.o
	${RM} *.d

# END
