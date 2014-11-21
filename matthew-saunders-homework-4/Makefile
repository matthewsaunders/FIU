all:	mpimm genmat prtmat

prtmat:	prtmat.o
	gcc prtmat.o -o prtmat

prtmat.o:	prtmat.c
	gcc -Wall -c prtmat.c -o prtmat.o

genmat:	genmat.o
	gcc genmat.o -o genmat

genmat.o:	genmat.c
	gcc -Wall -c genmat.c -o genmat.o

mpimm:	mpimm.c
	mpicc mpimm.c -o mpimm -lpthread -lm

mpimm.o:	mpimm.c
	gcc -Wall -c thmm.c -o thmm.o

clean:
	rm -f *.o *~ mpimm genmat prtmat
