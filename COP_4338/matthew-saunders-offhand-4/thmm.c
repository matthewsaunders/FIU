#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

struct mythread_t {
  pthread_t id; /* pthread id */
  int index; /* index in total thread count */
  int M, N, Q; /* matrix dimension A=MxN, B=NxQ */
  int P; /* number of threads */
  float **a, **b, **c; /* the three matrices */
};

/* read a matrix from a file */
void read_matrix(char* fname, float*** a, float** sa, int* m, int* n)
{
  FILE* finptr;
  int i, sz;

  finptr = fopen(fname, "r");
  if(!finptr) {
    perror("ERROR: can't open matrix file\n");
    exit(1); 
 }

  if(fread(m, sizeof(int), 1, finptr) != 1 ||
     fread(n, sizeof(int), 1, finptr) != 1) {
    perror("Error reading matrix file");
    exit(1);
  }
  sz = (*m)*(*n);

  *sa = (float*)malloc(sz*sizeof(float));
  if(fread(*sa, sizeof(float), sz, finptr) != sz) {
    perror("Error reading matrix file");
    exit(1);
  }

  *a = (float**)malloc((*m)*sizeof(float*));
  for(i=0; i<*m; i++) (*a)[i] = &(*sa)[i*(*n)];

  fclose(finptr);
}

/* write a matrix to a file */
void write_matrix(char* fname, float* sa, int m, int n)
{
  FILE* foutptr;
  int i;
  float* ptr;

  foutptr = fopen(fname, "w");
  if(!foutptr) {
    perror("ERROR: can't open matrix file\n");
    exit(1); 
 }
  if(fwrite(&m, sizeof(int), 1, foutptr) != 1 ||
     fwrite(&n, sizeof(int), 1, foutptr) != 1) {
    perror("Error reading matrix file");
    exit(1);
  }

  ptr = sa;
  for(i=0; i<m; i++) {
    if(fwrite(ptr, sizeof(float), n, foutptr) != n) {
      perror("Error reading matrix file");
      exit(1);
    }
    ptr += n;
  }

  fclose(foutptr);
}

void block_matmul(int index, int p, /* index of thread, total number of threads */
		  int m, int n, int q, /* matrices are M*N */
		  float** a, float** b, float** c) 
{
  int i, j, k;
  for(i=index; i<m; i+=p)
    for(j=0; j<q; j++)
      for(k=0; k<n; k++)
	c[i][j] += a[i][k]*b[k][j];
}

/* dumb matrix multiplication; used for debugging purposes */
void dumb_matmul(float** a, float** b, float** c, int M,int N, int Q) 
{
  block_matmul(0, 1, M, N, Q, a, b, c);
}

/* starting routing for threads */
void* work(void* arg)
{
  struct mythread_t* t = (struct mythread_t*)arg;

  block_matmul(t->index, t->P, t->M, t->N, t->Q, t->a, t->b, t->c);
  return 0;
}


/* call this function to do matrix multiplication */
void matmul(int p, float** a, float** b, float** c, int M, int N, int Q) 
{ 
  if(p == 1) dumb_matmul(a, b, c, M, N, Q);
  else {
    struct mythread_t *t, *k;
    int i;
    t = k = (struct mythread_t*)
      malloc(p*sizeof(struct mythread_t));

    //if more threads are requested than there are rows, set thread count to row count
    if(p>M)
      p = M;

    for(i=0; i<p; i++) {
	k->M = M; k->N = N; k->Q = Q; k->P = p;
	k->a = a; k->b = b; k->c = c, k->index = i;
	pthread_create(&k->id, 0, work, k);
	k++;
    }
    for(i=0; i<p; i++) {
      pthread_join(t[i].id, 0);
    }
    free(t);
  }
}

int main (int argc, char * argv[]) 
{
  int m, n, q; /* dimension of the matrix */
  float *sa, *sb, *sc; /* storage for matrix A, B, and C */
  float **a, **b, **c; /* 2-d array to access matrix A, B, and C */
  int i, j;

  if(argc != 5) {
    printf("Usage: %s num_threads fileA fileB fileC\n", argv[0]);
    return 1;
  }

  int p = atoi(argv[1]);
  if(p <= 0) { printf("ERROR: invalid number of threads!\n"); return 2; }

  /* read matrix A */
  read_matrix(argv[2], &a, &sa, &i, &j);
  m = i;
  n = j;

  /* read matrix B */
  read_matrix(argv[3], &b, &sb, &i, &j);
  q = j;
  if(n != i) { printf("ERROR: matrix A and B incompatible\n"); return 6; }

  /* initialize matrix C */
  sc = (float*)malloc(m*q*sizeof(float));
  memset(sc, 0, m*q*sizeof(float));
  c = (float**)malloc(m*sizeof(float*));
  for(i=0; i<m; i++) c[i] = &sc[i*q];

  /* do the multiplication */
  matmul(p, a, b, c, m, n, q);
  
  /* write matrix C */
  write_matrix(argv[4], sc, m, q);

  free(a); free(b); free(c);
  free(sa); free(sb); free(sc);
  return 0;
}
