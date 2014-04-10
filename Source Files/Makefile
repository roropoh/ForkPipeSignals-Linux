CC=gcc
FLAGS=-W -Wall

main: main.o output.o translate.o
	$(CC) -o assn1 main.o output.o translate.o

clean:
	rm -f *.o core.* assn1

main.o: main.c
	$(CC) $(FLAGS) -c main.c

output.o: output.c
	$(CC) $(FLAGS) -c output.c

translate.o: translate.c
	$(CC) $(FLAGS) -c translate.c