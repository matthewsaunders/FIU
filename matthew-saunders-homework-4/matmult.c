#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

/* Uncomment line to enable debugging */
//#define DEBUG

/* GLOBAL VARIABLES */
int m, n;	/* matrix dimensions */
int p;		/* total number of processes */
int id;		/* process rank */

/* process p-1 reads in the matrix n/p rows at a time and sends it to
   the other processes */
float* read_matrix(char* filename) { 
  FILE* fptr;		/* File containing matrix being read */
  float* storage_mat; 	/* Storage for matrix being read */
  int i;		/* Loop index */
  int chunk;		/* Size of each matrix subsection per process */
  MPI_Status status;	/* MPI status */

  /* open file */
  if(!(fptr = fopen(filename, "r"))){
    perror("ERROR: can't open matrix file\n");
    MPI_Finalize();
    exit(1);
  }

  /* reads in the dimension of the matrix (n x n); if not square
     matrix, quit */
  if(fread(&m, sizeof(int), 1, fptr) != 1 ||
     fread(&n, sizeof(int), 1, fptr) != 1){    
    perror("ERROR: reading matrix file");
    MPI_Finalize();
    exit(1);
  }  

  /* exit if the matrix is not square */
  if(m != n){
    perror("ERROR: matrix must be square\n");
    MPI_Finalize();
    exit(1);
  }

  /* exit if the matrix is not evenly divisible by the number of threads */
  if(n % p != 0){
    perror("ERROR: n not divisible by p\n");
    MPI_Finalize();
    exit(1);
  }  

  /* allocate an array 'storage_mat' of floats of n x (n/p) in size */
  chunk = n*(n/p);
  storage_mat = malloc(chunk*sizeof(float)); 
  
  if (id == p-1){ 
    for(i = 0; i < p; i++){
      /* read (n/p) rows of the matrix and fill in the array */
      if (fread(storage_mat, sizeof(float), chunk, fptr) != chunk){
	printf("ERROR: reading matrix file");
	MPI_Finalize();
	exit(1);
      }      

      if (i < p-1){
        /* mpi send the array storage_mat to process rank i */
	MPI_Send(storage_mat, chunk, MPI_FLOAT, i, 0, MPI_COMM_WORLD);	
      }
    }
  } 
  else {
    /* mpi receive the array storage_mat from process rank p-1 */
    MPI_Recv(storage_mat, chunk, MPI_FLOAT, p-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  }  

  /* debug section to display each matrix subsection per process */
  #ifdef DEBUG
  printf("\tp: %d, id: %d\n", p, id);
  printf("----> matrix '%s' section for process %d\n",filename, id);
  int j;
  for(i=0; i<n/p; i++){
    for(j=0; j<n; j++){
      printf("%4.2f ", (float)storage_mat[i*n/p + j]);
    }
    printf("\n");
  }
  #endif

  /* close file */
  fclose(fptr);
  return storage_mat;
}

/* process 0 writes out the matrix n/p rows at a time on behalf of all
   other processes */
void write_matrix(char* filename, float* storage_mat) {
  FILE* fout; 		/* File containing matrix being written */
  int chunk;		/* Size of each matrix subsection per process */
  int i;		/* Loop index */
  MPI_Status status;	/* MPI status */
  
  chunk = n*(n/p);

  /* open file */
  if(!(fout = fopen(filename, "w"))) {
    perror("ERROR: can't open matrix file\n");
    exit(1); 
  }  

  MPI_Barrier (MPI_COMM_WORLD);
  if(!id){
    /* reads in the dimension of the matrix */
    if(fwrite(&m, sizeof(int), 1, fout) != 1 ||
       fwrite(&n, sizeof(int), 1, fout) != 1) {
      perror("ERROR: writing matrix file first two");
      MPI_Finalize();
      exit(1);    
    }
    
    for(i = 0; i < p; i++){
      /* write (n/p) rows of the matrix from the array storage_mat */
      if(fwrite(storage_mat, sizeof(float), chunk, fout) != chunk){
	perror("ERROR: writing matrix");
	MPI_Finalize();
	exit(1);
      }
      if(i < p-1){
        /* mpi receive the array storage_mat from process rank i */
	MPI_Recv(storage_mat, chunk, MPI_FLOAT, i+1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      }
    }      
  } else {
    /* mpi send the array storage_mat to process rank 0 */
    MPI_Send(storage_mat, chunk, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
  }  
  /* close file */
  fclose(fout);  
}


int main(int argc, char *argv[]) {
  int i, j, k, l;	/* Loop indexes */
  float* storage_matA, *storage_matB, *storage_matC; /* storage for matrix A, B, and C */
  float **a, **b, **c;	/* 2-d array to access matrix A, B, and C */
  int chunk;		/* Size of each matrix subsection per process */
  int offset;		/* offset of matrix A during calculations of matrix C */
  MPI_Status status;	/* MPI status */
  
  /* initialize mpi, and find out the rank (id) and the total number
     of processes (p) */
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  /* parse command line arguments: fileA (the name of the file that
   contains the matrix A), fileB (the name of the file that contains
   matrix B), and fileC (the name of the file to store matrix C) */
  if(argc != 4){
    printf("Usage: %s fileA fileB fileC\n", argv[0]);
    MPI_Finalize();
    return -1;
  }
 
  /* allocate space and intialize to zero for storage_matC as an array
     of floats of n x (n/p) in size */
  storage_matA = read_matrix(argv[1]);
  storage_matB = read_matrix(argv[2]);
  chunk = n*(n/p);  
  storage_matC = malloc(chunk * sizeof(float));
  memset(storage_matC, 0, chunk * sizeof(float));
  
  /* create the auxiliary array of pointers so that the elements in A,
     B and C can be accessed using matA[i][j], etc. */  
  a = (float**)malloc((n/p)*sizeof(float*));  
  b = (float**)malloc((n/p)*sizeof(float*));
  c = (float**)malloc((n/p)*sizeof(float*));

  for (i=0; i<n/p; i++){ a[i] = &storage_matA [i*n];}
  for (i=0; i<n/p; i++){ b[i] = &storage_matB [i*n];} 
  for (i=0; i<n/p; i++){ c[i] = &storage_matC [i*n];} 
 
  /* calculate the partial sum for matC given the row band of A and
     B (see notes on row-wise matrix multiplication). */ 
  for(i = 0; i < p; i++){

    offset = ((id*(n/p)) + (i*(n/p))) % n;
    if(offset < 0){offset = -offset;}

    for(j = 0; j < (n/p); j++){
      for(k = 0; k < (n/p); k++){
	for(l = 0; l < n; l++){
	  c[j][l] += a[j][offset + k] * b[k][l];
	}
      }
    }
    /* mpi send storage_matB to the next process (id+1)%p */
    /* mpi receive storage_matB from the previous process */
    MPI_Sendrecv (storage_matB , chunk, MPI_FLOAT , (id+p-1)%p, 0, storage_matB, chunk, 
                  MPI_FLOAT, (id+1)%p, MPI_ANY_TAG, MPI_COMM_WORLD, &status) ;
  }  

  MPI_Barrier (MPI_COMM_WORLD);
  write_matrix(argv[3], storage_matC);
  
  /* reclaim matrices */
  free(a);
  free(b);
  free(c);
  free(storage_matA);
  free(storage_matB);
  free(storage_matC);

  /* Finalize MPI */
  MPI_Finalize();
  return 0;
}

