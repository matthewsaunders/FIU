all:	thmm genmat prtmat

prtmat:	prtmat.o
	gcc prtmat.o -o prtmat

prtmat.o:	prtmat.c
	gcc -Wall -c prtmat.c -o prtmat.o

genmat:	genmat.o
	gcc genmat.o -o genmat

genmat.o:	genmat.c
	gcc -Wall -c genmat.c -o genmat.o

thmm:	thmm.o
	gcc thmm.o -o thmm -lpthread -lm

thmm.o:	thmm.c
	gcc -Wall -c thmm.c -o thmm.o

clean:
	rm -f *.o *~ thmm genmat prtmat
