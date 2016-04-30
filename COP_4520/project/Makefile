all:	generateParticles printSnapshot p-p_sequential p-p_parallel

CFLAGS = -Wall
MPI = mpicc

#-------------------------------------------------------------------

p-p_parallel:	p-p_parallel.c commonUtilities.o
	mpicc p-p_parallel.c utilities.h commonUtilities.o -o p-p_parallel -lm

#-------------------------------------------------------------------

p-p_sequential:	p-p_sequential.o commonUtilities.o
	$(CC) utilities.h p-p_sequential.o commonUtilities.o -o $@ -lm
	
p-p_sequential.o: p-p_sequential.c
	$(CC) -Wall -c $< -o $@ -lm
	
commonUtilities.o:	commonUtilities.c
	$(CC) -Wall -c $< -o $@ -lm

printSnapshot:	printSnapshot.o
	$(CC) printSnapshot.o -o $@ -lm

printSnapshot.o:	printSnapshot.c
	$(CC) -Wall -c $< -o $@ -lm

generateParticles:	generateParticles.o
	$(CC) generateParticles.o -o $@ -lm

generateParticles.o:	generateParticles.c
	$(CC) -Wall -c $< -o $@ -lm

clean:
	rm -f generateParticles p-p_sequential p-p_parallel printSnapshot *.o core *~