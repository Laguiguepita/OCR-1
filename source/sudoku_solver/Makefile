# Simple mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`

all: solver

solver:solver.o


clean:
	${RM} *.o
	${RM} *.d
	${RM} solver

# END
