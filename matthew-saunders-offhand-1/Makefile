all:	f-c sizeof

f-c:	f-c.o
	gcc f-c.o -Wall -o f-c

f-c.o:	f-c.c
	gcc -c f-c.c -Wall -o f-c.o

sizeof:	sizeof.o
	gcc sizeof.o -Wall -o sizeof

sizeof.o:	sizeof.c
	gcc -c sizeof.c -Wall -o sizeof.o

clean:
	rm -f f-c f-c.o sizeof sizeof.o core *~
