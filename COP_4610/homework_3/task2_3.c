##########################################################
## COP4610 – Principles of Operating Systems – Summer C 2015
## Prof. Jose F. Osorio
## Group: group name
## Group Members:       Robert Hertzbach – 2676397
##                      Matthew Saunders – 2403246
## Project: Multithreaded Programming
## Specs:
## Due Date: 07/08/2015 by 11:55pm
## Module Name: task2_3.c
##
## We Certify that this program code has been written by us
## and no part of it has been taken from any sources.
##########################################################
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>     
 
#define N 50
 
int main (int argc, char *argv[]) {
int i, nthreads, tid;
float a[N], b[N], c[N], d[N];
 
/* Some initializations */
for (i=0; i<N; i++) {
  a[i] = i * 1.5;
  b[i] = i + 22.35;
  c[i] = d[i] = 0.0;
}
 
#pragma omp parallel shared(a,b,c,d,nthreads) private(i,tid) 
{
 tid = omp_get_thread_num();
 if (tid == 0) {
   nthreads = omp_get_num_threads();
   printf("Number of threads = %d\n", nthreads);
 }
 printf("Thread %d starting...\n",tid);
 
#pragma omp sections nowait 
{
 #pragma omp section 
 {
 printf("Thread %d doing section 1\n",tid);
 for (i=0; i<N; i++) {
    c[i] = a[i] + b[i];
   printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
 }
}
 
#pragma omp section 
{
  printf("Thread %d doing section 2\n",tid);
  for (i=0; i<N; i++) {
    d[i] = a[i] * b[i];
    printf("Thread %d: d[%d]= %f\n",tid,i,d[i]);
  }
 }
 
} /* end of sections */
 
printf("Thread %d done.\n",tid);
 
} /* end of parallel section */
 
        }

