all:	f-c sizeof

f-c:	f-c.o
	gcc f-c.o -o f-c

f-c.o:	f-c.c
	gcc -c f-c.c -o f-c.o

sizeof:	sizeof.o
	gcc sizeof.o -o sizeof

sizeof.o:	sizeof.c
	gcc -c sizeof.c -o sizeof.o

clean:
	rm -f f-c f-c.o sizeof sizeof.o core *~
