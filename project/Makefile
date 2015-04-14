all:	generateParticles p-p

CFLAGS = -Wall
MPI = mpicc

p-p:	p-p.o commonUtilities.o
	$(CC) utilities.h p-p.o commonUtilities.o -o $@ -lm
	
p-p.o: p-p.c
	$(CC) -Wall -c $< -o $@ -lm
	
commonUtilities.o:	commonUtilities.c
	$(CC) -Wall -c $< -o $@ -lm

generateParticles:	generateParticles.o
	$(CC) generateParticles.o -o $@ -lm

generateParticles.o:	generateParticles.c
	$(CC) -Wall -c $< -o $@ -lm

clean:
	rm -f generateParticles p-p *.o core *~