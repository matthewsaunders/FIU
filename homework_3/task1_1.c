#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
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

      #ifdef PTHREAD_SYNC
      printf("it works!");
      pthread_mutex_lock(&mutex);
      #endif
        val = SharedVariable;
        printf("*** thread %d sees value %d\n", which, val); SharedVariable = val + 1;
      #ifdef PTHREAD_SYNC
      pthread_mutex_unlock(&mutex);
      #endif
    }

  #ifdef PTHREAD_SYNC
  pthread_mutex_lock(&mutex);
  #endif
    val = SharedVariable;
  #ifdef PTHREAD_SYNC
  pthread_mutex_unlock(&mutex);
  #endif

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
    pthread_mutex_init(&mutex, NULL);

    if(argc < 2){
      printf("USAGE:\n\t./task1_1.c <#-threads>\n");
      exit(1);
    }

    /* Determine # of threads */
    numThreads = atoi(argv[1]);
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
    pthread_mutex_destroy(&mutex);
    free(t);
    return 0;
}
