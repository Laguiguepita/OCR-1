# Makefile

CC = gcc

CPPFLAGS = `pkg-config --cflags sdl gtk+-3.0` -MMD
CFLAGS = -Wall -Wextra -std=c99 -O3 -g #-fsanitize=address
LDFLAGS = #-fsanitize=address
LDLIBS = `pkg-config --libs sdl gtk+-3.0` -lSDL_image -lm

SRC = ${wildcard *.c} ${wildcard ../imagery_treatment/*.c}\
	 ${wildcard ../imagery_treatment/*/*.c}\
	 ${wildcard ../neural_network/*.c}\
	 ${wildcard ../neural_network/*/*.c}\
	 ${wildcard ../sudoku_solver/*.c}\


OBJ = ${SRC:.c=.o}
D = ${SRC:.c=.d}

app: ${OBJ}

clean:
	${RM} ${OBJ}
	${RM} ${D}
	${RM} ./Images/*
	${RM} ./cell/*
	rm app temp.bmp tmp.bmp



cleanCell:
	find -name "*cell[0-9][0-9]" | xargs rm


# END
