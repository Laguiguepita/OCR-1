main: main.o neural_network.o save_and_load.o
	gcc -lm -o main main.o neural_network.o save_and_load.o

main.o: main.c
	gcc -Wall -Wextra -Werror -c main.c

neural_network.o: neural_network.c
	gcc -Wall -Wextra -Werror -c neural_network.c

save_and_load.o: save_and_load.c
	gcc -Wall -Wextra -Werror -c save_and_load.c

clean:
	rm -f main *.o
