main: main.o neural_network.o
	gcc -lm -o main main.o neural_network.o

main.o: main.c
	gcc -Wall -Wextra -Werror -c main.c

neural_network.o: neural_network.c
	gcc -Wall -Wextra -Werror -c neural_network.c

clean:
	rm -f main *.o
