# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -lm
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image SDL_gfx`



rotation:manual_rotation.o 
clean:
	${RM} *.o
	${RM} *.d

# END
