all:
	gcc -g -Wall list.h list.c main.c -o out
debug:
	valgrind --tool=exp-sgcheck ./out
test:
	gcc -g -Wall list.h list.c testfile.c -o out