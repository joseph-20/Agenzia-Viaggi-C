out: main.o
	gcc main.o -o out

main.o: main.c
	gcc -c main.c