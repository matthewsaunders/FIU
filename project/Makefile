all:	generatePoints hermiteCode

CFLAGS = -Wall
MPI = mpicc

hermiteCode:	hermiteCode.o
	$(CC) hermiteCode.o -o $@
	
hermiteCode.o: hermiteCode.c
	$(CC) -Wall -c $< -o $@ -lm

generatePoints:	generatePoints.o
	$(CC) generatePoints.o -o $@ -lm

generatePoints.o:	generatePoints.c
	$(CC) -Wall -c $< -o $@ -lm

clean:
	rm -f generatePoints *.o core *~