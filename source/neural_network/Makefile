main: main.o neural_network.o save_and_load.o XOR.o data_set.o
	gcc -o main main.o neural_network.o save_and_load.o XOR.o data_set.o -lm

main.o: main.c
	gcc -Wall -Wextra -Werror -c main.c

neural_network.o: neural_network.c
	gcc -Wall -Wextra -Werror -c neural_network.c

save_and_load.o: save_and_load.c
	gcc -Wall -Wextra -Werror -c save_and_load.c

XOR.o: XOR.c
	gcc -Wall -Wextra -Werror -c XOR.c

data_set.o: data_set.c
	gcc -Wall -Wextra -Werror -c data_set.c


clean:
	rm -f main *.o
