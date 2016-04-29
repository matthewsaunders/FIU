CC=gcc
CFLAGS=-Wall
PT=-pthread
MP=-fopenmp

all:	task1_1 task1_2 task1_3 helloworld task2_2 task2_2b task2_3 task2_4 task2_4a task2_4b task2_4c task3

task3:		task3.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task2_4c:	task2_4c.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task2_4b:	task2_4b.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task2_4a:	task2_4a.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task2_4:	task2_4.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task2_3:	task2_3.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task2_2b:	task2_2b.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task2_2:	task2_2.c
	$(CC) $(CFLAGS) $(MP) $< -o $@

task1_3:	task1_3.c
	$(CC) $(CFLAGS) $(PT) $< -o $@

task1_1:	task1_1.c
	$(CC) $(CFLAGS) $(PT) $< -o $@

task1_2:	task1_2.c
	$(CC) $(CFLAGS) $(PT) -DPTHREAD_SYNC $< -o $@

helloworld:	OpenMP/helloworld.c
	$(CC) -fopenmp $< -o OpenMP/$@

clean:
	rm -f *.o core *.~ task1_1 task1_2 task1_3 OpenMP/helloworld task2_2 task2_2b task2_3 task2_4 task2_4a task2_4b task2_4c task3
