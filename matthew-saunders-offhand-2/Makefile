all:	task-2 task-3	

task-2:	calc.o
	gcc calc.o -Wall -o task-2

task-3: calc.o
        gcc calc.o -Wall -o task-3

calc:	calc.o
	gcc calc.o -Wall -o calc

calc.o: calc.h	
	gcc -c calc.h -Wall -o calc.o 

getop:   getop.o
        gcc getop.o -Wall -o getop 

getop.o: getop.c
        gcc -c getop.c -Wall -o getop.o

main:   main.o
        gcc main.o -Wall -o main 

main.o: main.c 
        gcc -c main.c -Wall -o main.o 

stack:   stack.o
        gcc stack.o -Wall -o stack 

stack.o: stack.h
        gcc -c stack.c -Wall -o stack.o

getch:   getop.o
        gcc getch.o -Wall -o getch

getch.o: getch.c
        gcc -c getch.c -Wall -o getch.o

clean:
	rm -f core *~
