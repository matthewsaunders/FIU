all:	generateParticles hermiteCode

CFLAGS = -Wall
MPI = mpicc

hermiteCode:	hermiteCode.o
	$(CC) hermiteCode.o -o $@
	
hermiteCode.o: hermiteCode.c
	$(CC) -Wall -c $< -o $@ -lm

generateParticles:	generateParticles.o
	$(CC) generateParticles.o -o $@ -lm

generateParticles.o:	generateParticles.c
	$(CC) -Wall -c $< -o $@ -lm

clean:
	rm -f generateParticles hermiteCode *.o core *~