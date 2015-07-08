##########################################################
## COP4610 – Principles of Operating Systems – Summer C 2015
## Prof. Jose F. Osorio
## Group: group name
## Group Members:       Robert Hertzbach – 2676397
##                      Matthew Saunders – 2403246
## Project: Multithreaded Programming
## Specs:
## Due Date: 07/08/2015 by 11:55pm
## Module Name: task1_1.c
##
## We Certify that this program code has been written by us
## and no part of it has been taken from any sources.
##########################################################
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_barrier_t   barrier;
int SharedVariable = 0;

struct mythread {
  pthread_t id; /* thread id */
  int idx; /* thread index (0 .. p-1) */
};


void SimpleThread(int which) {
    int num, val;
    for(num = 0; num < 20; num++) {
      if (random() > RAND_MAX / 2)
        usleep(10);

        val = SharedVariable;
        printf("*** thread %d sees value %d\n", which, val); SharedVariable = val + 1;
    }

    val = SharedVariable;

  printf("Thread %d sees final value %d\n", which, val);
}

void* callSimpleThread(void *arg){
  struct mythread* t = (struct mythread*)arg;
  SimpleThread(t->idx);
  return 0;
}

int main (int argc, char *argv[]) {

    int i = 0;
    int numThreads;
    struct mythread* t;

    if(argc < 2){
      printf("USAGE:\n\t./task1_1.c <#-threads>\n");
      exit(1);
    }

    /* Determine # of threads */
    numThreads = atoi(argv[1]);
    pthread_barrier_init (&barrier, NULL, numThreads);
    printf("Executing for %d threads\n", numThreads);

    /* Create threads */
    t = (struct mythread*)malloc(numThreads*sizeof(struct mythread));
    for(i=0; i<numThreads; i++) {
      t[i].idx = i;
      pthread_create(&t[i].id, 0, callSimpleThread, &t[i]);
    }

    for(i = 0; i < numThreads; i++){
      pthread_join(t[i].id, 0);
    }

    pthread_exit(NULL);
    free(t);
    return 0;
}
