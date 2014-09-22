all:	polish	

polish:	calc.o getop.o main.o stack.o getch.o
	gcc calc.h getop.o main.o stack.o getch.o -Wall -o polish

calc.o: calc.h	
	gcc -c calc.h -Wall -o calc.o 

getop.o: getop.c
	gcc -c getop.c -Wall -o getop.o

main.o: main.c 
	gcc -c main.c -Wall -o main.o 

stack.o: stack.c
	gcc -c stack.c -Wall -o stack.o

getch.o: getch.c
	gcc -c getch.c -Wall -o getch.o

clean:
	rm -f *.o  core *~ polish
