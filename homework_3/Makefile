CC=gcc
CFLAGS=-Wall
PT=-pthread
MP=-fopenmp

all:	task1 helloworld task2_2 task2_2b task2_3

task2_3:	task2_3.c
	$(CC) $(MP) $< -o $@

task2_2b:	task2_2b.c
	$(CC) $(MP) $< -o $@

task2_2:	task2_2.c
	$(CC) $(MP) $< -o $@

task1:	task1.c
	$(CC) $(CFLAGS) $(PT) $< -o $@

helloworld:	helloworld.c
	$(CC) -fopenmp $< -o $@

clean:
	rm -f *.o core *.~ task1 helloworld task2_2 task2_2b task2_3
