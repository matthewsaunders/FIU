all:	matmult genmat prtmat

CFLAGS = -O3 -Wall
MPI = mpicc

matmult:	matmult.c
	$(MPI) $(CFLAGS) $< -o $@

genmat:	genmat.c
	$(CC) $(CFLAGS) $< -o $@

prtmat:	prtmat.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) matmult genmat prtmat *~
