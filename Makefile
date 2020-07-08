entrada.o: entrada.c
	gcc -c entrada.c -o entrada.o

pecas.o : pecas.c
	gcc -c pecas.c -o pecas.o

tab.o : tab.c
	gcc -c tab.c -o tab.o

jogada.o: jogada.c
	gcc -c jogada.c -o jogada.o

main.o: main.c
	gcc -c main.c -o main.o

qwirkle: entrada.o pecas.o tab.o jogada.o main.o
	gcc -o qwirkle *.o

all: qwirkle

run: all
	./qwirkle

clean: entrada.o pecas.o tab.o jogada.o main.o qwirkle
	rm *.o qwirkle

zip: struct.h entrada.c entrada.h pecas.c pecas.h tab.c tab.h jogada.c jogada.h main.c
	zip qwirkle.zip Makefile *.c *.h	
