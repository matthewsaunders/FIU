all:	matmult

CFLAGS = -O3 -Wall
MPI = mpicc

matmult:	matmult.c
	$(MPI) $(CFLAGS) $< -o $@

clean:
	$(RM) matmult *~
