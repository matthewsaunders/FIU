all:	find

find:	find.o getline.o
	gcc find.o getline.o -Wall -o find

find.o:	find.c
	gcc -c find.c -o find.o

getline.o:	getline.c
	gcc -c getline.c -o getline.o

clean:
	rm -f *.o  core *~ find
