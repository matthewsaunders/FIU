all:	find

find:	find.o
	gcc find.o -Wall -o find

find.o:	find.c
	gcc -c find.c -o find.o

clean:
	rm -f *.o  core *~ find
