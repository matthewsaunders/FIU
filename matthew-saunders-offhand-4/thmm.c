#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mythread_t {
  pthread_t id; /* pthread id */
  int x, y; /* thread coordinates (0..P-1, 0..P-1) */
  int N; /* matrix dimension NxN */
  int P; /* number of threads in one dimension; there are PxP number of threads */
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

void block_matmul(int crow, int ccol, /* corner of C block */
		  int arow, int acol, /* corner of A block */
		  int brow, int bcol, /* corner of B block */
		  int n, /* block size */
		  int N, /* matrices are N*N */
		  float** a, float** b, float** c) 
{
  int i, j, k;
  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      for(k=0; k<n; k++)
	c[crow+i][ccol+j] += a[arow+i][acol+k]*b[brow+k][bcol+j];
}

/* dumb matrix multiplication; used for debugging purposes */
void dumb_matmul(float** a, float** b, float** c, int N) 
{
  /*
  int i, j, k;
  for(i=0; i<N; i++)
    for(j=0; j<N; j++)
      for(k=0; k<N; k++)
	c[i][j] += a[i][k]*b[k][j];
  */
  block_matmul(0, 0, 0, 0, 0, 0, N, N, a, b, c);
}

/* starting routing for threads */
void* work(void* arg)
{
  struct mythread_t* t = (struct mythread_t*)arg;
  int n = t->N/t->P, i;
  for(i = 0; i<t->P; i++) {
    block_matmul(n*t->x, n*t->y, n*t->x, n*i, n*i, n*t->y,
		 n, t->N, t->a, t->b, t->c);
  }
  return 0;
}


/* call this function to do matrix multiplication */
void matmul(int p, float** a, float** b, float** c, int N) 
{ 
  if(p == 1) dumb_matmul(a, b, c, N);
  else {
    struct mythread_t *t, *k;
    int i, j;
    t = k = (struct mythread_t*)
      malloc(p*p*sizeof(struct mythread_t));
    for(i=0; i<p; i++) {
      for(j=0; j<p; j++) {
	k->x = i; k->y = j; k->N = N; k->P = p;
	k->a = a; k->b = b; k->c = c;
	pthread_create(&k->id, 0, work, k);
	k++;
      }
    }
    for(i=0; i<p*p; i++) {
      pthread_join(t[i].id, 0);
    }
    free(t);
  }
}

int main (int argc, char * argv[]) 
{
  int n; /* dimension of the matrix */
  float *sa, *sb, *sc; /* storage for matrix A, B, and C */
  float **a, **b, **c; /* 2-d array to access matrix A, B, and C */
  int i, j;

  if(argc != 5) {
    printf("Usage: %s num_threads fileA fileB fileC\n", argv[0]);
    return 1;
  }

  int pp = atoi(argv[1]);
  if(pp <= 0) { printf("ERROR: invalid number of threads!\n"); return 2; }
  int p = (int)sqrt(pp);
  if(p*p != pp) { printf("ERROR: #threads not square number!\n"); return 3; }

  /* read matrix A */
  read_matrix(argv[2], &a, &sa, &i, &j);
  if(i != j) { printf("ERROR: matrix A not square\n"); return 4; }
  n = i;

  /* read matrix B */
  read_matrix(argv[3], &b, &sb, &i, &j);
  if(i != j) { printf("ERROR: matrix B not square\n"); return 5; }
  if(n != i) { printf("ERROR: matrix A and B incompatible\n"); return 6; }
  if(n/p*p != n) { printf("ERROR: matrix dimension cannot be divided by p.\n"); return 7; }

  /* initialize matrix C */
  sc = (float*)malloc(n*n*sizeof(float));
  memset(sc, 0, n*n*sizeof(float));
  c = (float**)malloc(n*sizeof(float*));
  for(i=0; i<n; i++) c[i] = &sc[i*n];

  /* do the multiplication */
  matmul(p, a, b, c, n);
  
  /* write matrix C */
  write_matrix(argv[4], sc, n, n);

  free(a); free(b); free(c);
  free(sa); free(sb); free(sc);
  return 0;
}
