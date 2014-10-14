all: bstsort

bstsort: bstsort.o strCompare.o 
	gcc bstsort.o strCompare.o bstsort.h -o bstsort

bstsort.o: bstsort.c
	gcc -c bstsort.c -Wall -o bstsort.o

strCompare.o: strCompare.c	
	gcc -c strCompare.c -Wall -o strCompare.o

clean:
	rm -f bstsort core *~ *.o strCompare
