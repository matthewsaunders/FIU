#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define DEBUG 

/* GLOBAL SCOPE */
int p; /* total number of processes */
int id; /* process rank */
MPI_Status status; /* MPI status */
int *m, *n; /*matrix dimensions */

/* process p-1 reads in the matrix n/p rows at a time and sends it to
   the other processes */
float* read_matrix(char* filename)
{ 
  float* storage_mat; /* storage array for chunk of matrix */
  FILE* finptr; /* file with matrix being read */
  //int *m, *n;
  float* ptr;
  int i, j;

  m = (int*)malloc(sizeof(int));
  n = (int*)malloc(sizeof(int));

  /* open file */
  finptr = fopen(filename, "r");
  if(!finptr) { perror("ERROR: can't open matrix file\n"); exit(1); }

  /* reads in the dimension of the matrix (n x n); if not square
     matrix, quit */
  if(fread(m, sizeof(int), 1, finptr) != 1 ||
     fread(n, sizeof(int), 1, finptr) != 1){
    perror("Error reading matrix file");
    exit(1);
  }

  if((*m) != (*n)) { printf("ERROR: matrix A not square\n"); exit(2); }
  if(((*n)%p) != 0) { printf("ERROR: number of processes P is not evenly divisible\n"); exit(2); }

  /* allocate an array 'storage_mat' of floats of n x (n/p) in size */
  storage_mat = (float*)malloc((*n)*((*n)/p)*sizeof(float));

  if(id == p-1) {
    for(i=0; i<p; i++) {
      /* read (n/p) rows of the matrix and fill in the array */
      ptr = storage_mat;
      for(j=0; j<((*n)/p); j++) {
        if(fread(ptr, sizeof(float), (*n), finptr) != (*n)) {
          perror("Error reading matrix file");
          exit(1);
        }
        ptr += (*n);
      }

      if(i < p-1) {
        /* mpi send the array storage_mat to process rank i */
        MPI_Send(storage_mat, (*n)*(*n)/p, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
      }
    }
  } else {
    /* mpi receive the array storage_mat from process rank p-1 */
    MPI_Recv(storage_mat, (*n)*(*n)/p, MPI_FLOAT, p-1, 0, MPI_COMM_WORLD, &status);
  }  

#ifdef DEBUG
  printf("...In function read_matrix\n");
  printf("\tp: %d, id: %d\n", p, id);
  printf("----> matrix section for process %d\n",id);
  ptr = storage_mat;
  for(i=0; i<(*n)/p; i++){
    for(j=0; j<(*n); j++){
      printf("%4.2f ", (float)storage_mat[i*(*n)/p + j]);
    }
    printf("\n");
  }
#endif

  /* close file */
  fclose(finptr);
  return storage_mat;
}

/* process 0 writes out the matrix n/p rows at a time on behalf of all
   other processes */
void write_matrix(char* filename, float* storage_mat)
{
  printf("..in function write_matrix\n");
  int i;

  /* open file */
  if(!id) {
    for(i=0; i<p; i++) {
      /* write (n/p) rows of the matrix from the array storage_mat */
      if(i < p-1) {
	/* mpi receive the array storage_mat from process rank i */
      }
    }
  } else {
    /* mpi send the array storage_mat to process rank 0 */
    //MPI_Send(storage_mat, (*n)*(*n)/p, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
  }
  /* close file */
  return;
}

int main(int argc, char* argv[])
{
  int i, j;
  char* fileA; /* file containing matrix A */
  char* fileB; /* file containing matrix B */
  char* fileC; /* file containing matrix C */
  float *storage_matA, *storage_matB, *storage_matC; /* storage for matrix A, B, and C */
  float **a, **b, **c; /* 2-d array to access matrix A, B, and C */
  int x, y, z;

  /* initialize mpi, and find out the rank (id) and the total number
     of processes (p) */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  /* parse command line arguments: fileA (the name of the file that
     contains the matrix A), fileB (the name of the file that contains
     matrix B), and fileC (the name of the file to store matrix C) */
  if(argc != 4) {
    printf("Usage: %s fileA fileB fileC\n", argv[0]);
    return 1;
  }

  fileA = argv[1];
  fileB = argv[2];
  fileC = argv[3];

  /* allocate space and intialize to zero for storage_matC as an array
     of floats of n x (n/p) in size */
  storage_matA = read_matrix(fileA);
  storage_matB = read_matrix(fileB);
  printf("--> ok in main %d\n",id);

  storage_matC = (float*)malloc((id*id/p)*sizeof(float));
  memset(storage_matC, 0, sizeof((id*id/p)*sizeof(float)));

  /* create the auxiliary array of pointers so that the elements in A,
     B and C can be accessed using matA[i][j], etc. */
  a = (float**)malloc((id/p)*sizeof(float*));
  b = (float**)malloc((id/p)*sizeof(float*));
  c = (float**)malloc((id/p)*sizeof(float*));

  for(i=0; i<(*m); i++) a[i] = &storage_matA[i*(*m)]; 
  for(i=0; i<(*m); i++) b[i] = &storage_matB[i*(*m)]; 
  for(i=0; i<(*m); i++) c[i] = &storage_matC[i*(*m)]; 

  for(i=0; i<p; i++) {
    /* calculate the partial sum for matC given the row band of A and
     B (see notes on row-wise matrix multiplication). */

    for(x=0; x<(*n)/p; x++){
     for(y=0; y<(*n); y++){
      for(z=0; z<(*n); z++){
        c[x][z] += a[x][z] * b[y][z];  
      }
     }
    }

    if(i < p-1) {
      /* mpi send storage_matB to the next process (id+1)%p */


      /* mpi receive storage_matB from the previous process */


    }
  }
  
  //write_matrix(fileC, storage_matC);

  /* reclaim matrices, finalize mpi */
  free(storage_matA);
  printf("--> ok at end1 %d\n",id);
  MPI_Finalize();
  printf("--> ok at end2 %d\n",id);
  return 0;
}
