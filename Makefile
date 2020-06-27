main.o : main.c
	gcc -c main.c -o main.o

imprimetab.o : imprimetab.c
	gcc -c imprimetab.c -o imprimetab.o

jogo : main.o imprimetab.o
	gcc -o jogo *.o

all : jogo

run : all
	./jogo
