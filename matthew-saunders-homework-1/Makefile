all: strCompare

strCompare: strCompare.o
	gcc strCompare.o -Wall -o strCompare

strCompare.o: strCompare.c	
	gcc -c strCompare.c -Wall -o strCompare.o

clean:
	rm -f btsort core *~ *.o strCompare
