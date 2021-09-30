all:
	gcc -g -Wall list.h list.c main.c -o out
clean:
	rm out
