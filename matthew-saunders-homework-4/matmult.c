#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

float* read_matrix(fileA){
  float* storage; /* storage array for chunk of matrix */

  return storage;
}

void write_matrix(fileC, storage_matC){


  return;
}

int main(int argc, char* argv[])
{
  int p; /* total number of processes */
  int id; /* process rank */
  int i;
  char* fileA; /* file containing matrix A */
  char* fileB; /* file containing matrix B */
  char* fileC; /* file containing matrix C */
  float *storage_matA, *storage_matB, *storage_matC; /* storage for matrix A, B, and C */
  float **a, **b, **c; /* 2-d array to access matrix A, B, and C */

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

  storage_matA = read_matrix(fileA);
  storage_matB = read_matrix(fileB);

  /* allocate space and intialize to zero for storage_matC as an array
     of floats of n x (n/p) in size */
  storage_matA = (float*)malloc(id*(id/p)*sizeof(float));
  storage_matB = (float*)malloc(id*(id/p)*sizeof(float));
  storage_matC = (float*)malloc(id*(id/p)*sizeof(float));

  /* create the auxiliary array of pointers so that the elements in A,
     B and C can be accessed using matA[i][j], etc. */
  a = (float**)malloc((id/p)*sizeof(float*));
  b = (float**)malloc((id/p)*sizeof(float*));
  c = (float**)malloc((id/p)*sizeof(float*));

  for(i=0; i<p; i++) {
  /* calculate the partial sum for matC given the row band of A and
     B (see notes on row-wise matrix multiplication). */
    
    if(i < p-1) {
      /* mpi send storage_matB to the next process (id+1)%p */
      /* mpi receive storage_matB from the previous process */
    }
  }
  
  write_matrix(fileC, storage_matC);

  /* reclaim matrices, finalize mpi */
  MPI_Finalize();
  return 0;
}
