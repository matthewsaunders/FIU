all: bstsort strCompare

bstsort: bstsort.o 
	gcc bstsort.o -o bstsort

bstsort.o: bstsort.c
	gcc -c bstsort.c -Wall -o bstsort.o

strCompare: strCompare.o
	gcc strCompare.o -Wall -o strCompare

strCompare.o: strCompare.c	
	gcc -c strCompare.c -Wall -o strCompare.o

clean:
	rm -f bstsort core *~ *.o strCompare
