all:	euler_forward

CFLAGS = -Wall
MPI = mpicc

euler_forward:	euler_forward.o
	$(CC) euler_forward.o -o $@ -lm

euler_forward.o:	euler_forward.c
	$(CC) -Wall -c $< -o $@ -lm

clean:
	rm -f euler_forward *.o core *~
