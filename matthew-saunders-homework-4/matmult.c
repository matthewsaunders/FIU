#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

//#define DEBUG 

/* GLOBAL SCOPE */
int p; /* total number of processes */
int id; /* process rank */
MPI_Status status; /* MPI status */
MPI_Request request; /* MPI status */
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
        ptr += (*n)/p;
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
  //printf("..in function write_matrix\n");
  int i;
  FILE* foutptr;
  float* ptr;

  /* open file */
  foutptr = fopen(filename, "w");
  if(!foutptr) { perror("ERROR: can't open matrix file\n"); exit(1); }

  if(fwrite(m, sizeof(int), 1, foutptr) != 1 ||
     fwrite(n, sizeof(int), 1, foutptr) != 1) {
    perror("Error writing matrix file");
    exit(1);
  }

  ptr = storage_mat;

  if(!id) {
    for(i=0; i<p; i++) {
      /* write (n/p) rows of the matrix from the array storage_mat */
      for(i=0; i<(*m); i++) {
        if(fwrite(ptr, sizeof(float), (*n), foutptr) != (*n)) {
          perror("Error reading matrix file");
          exit(1);
        }      
	  }

      if(i < p-1) {
        /* mpi receive the array storage_mat from process rank i */
        MPI_Recv(storage_mat, (*n)*(*n)/p, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &status);
      }
    }
  } else {
    /* mpi send the array storage_mat to process rank 0 */
    MPI_Send(storage_mat, (*n)*(*n)/p, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
  }
  /* close file */
  return;
}


int main(int argc, char* argv[])
{
  int i;
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

  int j;
  float* ptr;
  printf("\tp: %d, id: %d\n", p, id);
  printf("----> matrix section for process %d\n",id);
  ptr = storage_matA;
  for(i=0; i<(*n)/p; i++){
    for(j=0; j<(*n); j++){
      printf("%4.2f ", (float)storage_matA[i*(*n)/p + j]);
    }
    printf("\n");
  }



  storage_matC = (float*)malloc((id*id/p)*sizeof(float));
  memset(storage_matC, 0, sizeof((id*id/p)*sizeof(float)));

  /* create the auxiliary array of pointers so that the elements in A,
     B and C can be accessed using matA[i][j], etc. */
  a = (float**)malloc(((*n)/p)*sizeof(float*));
  b = (float**)malloc(((*n)/p)*sizeof(float*));
  c = (float**)malloc(((*n)/p)*sizeof(float*));

  for(i=0; i<(*n)/p; i++){ a[i] = &storage_matA[i*(*m)];}
  for(i=0; i<(*n)/p; i++){ b[i] = &storage_matB[i*(*m)];}
  for(i=0; i<(*n)/p; i++){ c[i] = &storage_matC[i*(*m)];} 


  printf("LOOK HERE\n");
  for(i=0; i<(*n)/p; i++){ 
    for(j=0; j<(*n); j++){
     printf("a[%d,%d] = %4.2f %p\n",i,j, (float)a[i][j], &a[i][j]);
    }
  } 

  //printf("--> before calc %d\n",id);
  for(i=0; i<p; i++) {
    /* calculate the partial sum for matC given the row band of A and
     B (see notes on row-wise matrix multiplication). */

    printf("x: %d, y,z: %d\n", (*n)/p, (*n));
    //for(x=0; x<(*n)/p; x++){
    for(x=0; x<4; x++){
     //for(y=0; y<(*n); y++){
     for(y=0; y<4; y++){
     // for(z=0; z<(*n); z++){
        printf("%d - (%d,%d): %4.2f --> ",id, x, y, (float)c[x][y]);
        c[x][y] += (float)a[x][y] * (float)b[x][y];  
        //c[x][y] += a[x][y] * b[x][y];  
        printf("%4.2f ........ %4.2f %4.2f %p\n", (float)c[x][y], (float)a[x][y], (float)b[x][y]), &a[x][y];
      //}
     }
    }

    if(i < p-1) {
      /* mpi send storage_matB to the next process (id+1)%p */
      MPI_Isend(storage_matB, (*n)*(*n)/p, MPI_FLOAT, (id+1)%p, 0, MPI_COMM_WORLD, &request);

      /* mpi receive storage_matB from the previous process */
      MPI_Irecv(storage_matB, (*n)*(*n)/p, MPI_FLOAT, (id+(p-1))%p, 0, MPI_COMM_WORLD, &request);
    }
  }
  printf("--> after calc %d\n",id);

  //storage_matC = storage_matA; 
 
  //write_matrix(fileC, storage_matC);
  printf("--> after write %d\n",id);

  /* reclaim matrices, finalize mpi */
  free(storage_matA);
  free(storage_matB);
  //free(storage_matC);
  free(a);
  free(b);
  free(c);
  free(m);
  free(n);
  MPI_Finalize();
  return 0;
}
