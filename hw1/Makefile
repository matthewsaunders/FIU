all:	helloworld

helloworld:	helloworld.o
	gcc helloworld.o -o helloworld

helloworld.o:	helloworld.c
	gcc -c helloworld.c -o helloworld.o

clean:
	rm -f helloworld helloworld.o core *~
