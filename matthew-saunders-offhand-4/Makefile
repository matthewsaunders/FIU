all:	seqmm thmm genmat prtmat

CFLAGS = -O3 -Wall

seqmm:	seqmm.c
	$(CC) $(CFLAGS) $< -o $@

thmm:	thmm.c
	$(CC) $(CFLAGS) $< -o $@

genmat:	genmat.c
	$(CC) $(CFLAGS) $< -o $@

prtmat:	prtmat.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) seqmm thmm genmat prtmat *~
