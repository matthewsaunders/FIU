#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <mpi.h>

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
void write_matrix(char* fname, float* sa, int m, int n, int id, int p)
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
      perror("Error writing matrix file");
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
  for(i=index; i<m; i+=p){
    printf("rank: %d, # processes: %d, line #: %d\n",index,p,i);
    for(j=0; j<q; j++)
      for(k=0; k<n; k++)
	c[i][j] += a[i][k]*b[k][j];
  }
}

/* dumb matrix multiplication; used for debugging purposes */
void dumb_matmul(float** a, float** b, float** c, int M,int N, int Q) 
{
  block_matmul(0, 1, M, N, Q, a, b, c);
}

int main (int argc, char * argv[]) 
{
  int m, n, q; /* dimension of the matrix */
  float *sa, *sb, *sc; /* storage for matrix A, B, and C */
  float **a, **b, **c; /* 2-d array to access matrix A, B, and C */
  int i, j;
  int id; /* process rank */
  int p; /* number of processes */

  if(argc != 4) {
    printf("Usage: %s fileA fileB fileC\n", argv[0]);
    return 1;
  }

  /* read matrix A */
  read_matrix(argv[1], &a, &sa, &i, &j);
  m = i;
  n = j;

  /* read matrix B */
  read_matrix(argv[2], &b, &sb, &i, &j);
  q = j;
  if(n != i) { printf("ERROR: matrix A and B incompatible\n"); return 6; }

  /* initialize matrix C */
  sc = (float*)malloc(m*q*sizeof(float));
  memset(sc, 0, m*q*sizeof(float));
  c = (float**)malloc(m*sizeof(float*));
  for(i=0; i<m; i++) c[i] = &sc[i*q];

  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  /* do the multiplication */
  if(p == 1) dumb_matmul(a, b, c, m, n, q);
  else {
    //if more threads are requested than there are rows, set thread count to row count
    if(p>m)
      p = m; 

    struct mythread_t *t, *k;
    t = k = (struct mythread_t*) malloc(sizeof(struct mythread_t));

    printf("MPI rank %d of %d\n", id, p);
 
    k->M = m; k->N = n; k->Q = q, k->P = p;
    k->a = a; k->b = b; k->c = c, k->index = id;

    block_matmul(k->index, k->P, k->M, k->N, k->Q, k->a, k->b, k->c);

    free(k);
  }
 
  /* write matrix C */
  MPI_Barrier (MPI_COMM_WORLD);
  if(!id)
    write_matrix(argv[3], sc, m, q, id, p);

  MPI_Finalize();

  free(a); free(b); free(c);
  free(sa); free(sb); free(sc);
  return 0;
}
