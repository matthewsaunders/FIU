##########################################################
## COP4610 – Principles of Operating Systems – Summer C 2015
## Prof. Jose F. Osorio
## Group: group name
## Group Members:       Robert Hertzbach – 2676397
##                      Matthew Saunders – 2403246
## Project: Multithreaded Programming
## Specs:
## Due Date: 07/08/2015 by 11:55pm
## Module Name: task2_2b.c
##
## We Certify that this program code has been written by us
## and no part of it has been taken from any sources.
##########################################################
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
 
#define CHUNKSIZE    10
#define N                       100
 
int main (int argc, char *argv[]) {
int nthreads, tid, i, chunk;
float a[N], b[N], c[N];
 
 
for (i=0; i < N; i++)
     a[i] = b[i] = i * 1.0; // initialize arrays
 
chunk = CHUNKSIZE;

double time = -omp_get_wtime(); 
 
#pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid) 
{
  tid = omp_get_thread_num();
 
  if (tid == 0) {
     nthreads = omp_get_num_threads();
     printf("Number of threads = %d\n", nthreads);
  }
 
  printf("Thread %d starting...\n",tid);
 
 
  #pragma omp parallel for
  for (i=0; i<N; i++) {
       c[i] = a[i] + b[i];
      printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
  }
 
} /* end of parallel section */
 
time += omp_get_wtime();
printf("Time of execution: %10.8f\n",time);

}
