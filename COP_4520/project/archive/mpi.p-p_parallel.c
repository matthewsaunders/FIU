/*------------------------------------------------------------------------------
 * usage: 
 * $ cat out | ./p-p 10000 2>&1
 *
 *------------------------------------------------------------------------------
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>
#include "utilities.h"

/* block decomposition macros */
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

void evolve(double *mass, double **pos, double **vel, double **acc, 
			int n, double t, double dt, double t_out, double dt_out, double t_end, FILE* fout);



int main(int argc, char* argv[]){
	double elapsed_time;
	int n = 0;				// get n count from command line
	double t = 0.0;			// assume time is zero
	double dt = 0.001;		//time step
	double t_end = 1.0;		//final time
	double t_out = 0.0;
	double dt_out = 0.1;	
	FILE* fptr;
	FILE* fout;
	int p; /* the number of MPI processes */
  	int id; /* the rank of this process */
  	MPI_Status status;
	int i,j;
	double *mass;
	double **pos, **vel, **acc;
	double *storage_pos, *storage_vel, *storage_acc;
	double *my_mass;	//holds subsection of mass
	double **my_pos, **my_vel, **my_acc;	//holds subsection of arrays
	double **vector[3];
	
  	MPI_Init(&argc, &argv);
 	MPI_Comm_size(MPI_COMM_WORLD, &p);
 	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	elapsed_time = - clock();
	
	if(argc != 3){
		printf("usage: \n\t%s ", argv[0]);
		printf("[input file] [output file]\n");
		MPI_Abort (MPI_COMM_WORLD, -1);
		return 1;
	}
	
	if(!id){
		if( !(fptr = fopen (argv[1], "r")) ) {
			perror("ERROR: can't open data file\n");
			MPI_Abort (MPI_COMM_WORLD, -1);
			return 2;
		}

		if( !(fout = fopen (argv[2], "w")) ) {
			perror("ERROR: can't open data file\n");
			MPI_Abort (MPI_COMM_WORLD, -1);
			return 2;
		}
		/* parse arguments, initialize position and velocity */
		if(fread(&n, sizeof(int), 1, fptr) != 1 || fread(&t, sizeof(double), 1, fptr) != 1) {
			perror("Error reading data file");
			MPI_Abort (MPI_COMM_WORLD, -1);
			return 3;
		}
	}
		
	MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (!(&n)) MPI_Abort (MPI_COMM_WORLD, -1);
	
	MPI_Bcast (&t, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if (!(&t)) MPI_Abort (MPI_COMM_WORLD, -1);
	//printf("N: %d\nt: %f\n", n, t);
	printf("N: %d\t: %f\t %d\n", n, t, id);
	printf("flag 1\n");
	storage_pos = malloc(n*NDIM*sizeof(double));
	printf("flag 2\n");
	//create storage array and read in data
	if(!id){
		mass = (double*)malloc(n*sizeof(double));

		//storage_pos = malloc(n*NDIM*sizeof(double));
		

		//storage_vel = malloc(n*NDIM*sizeof(double));
		/*
		vel = (double**)malloc(n*sizeof(double*));
		for(i=0; i<n; i++)
			vel[i] = &storage_vel[i*NDIM];
		*/
		//storage_acc = malloc(n*NDIM*sizeof(double));
		/*
		acc = (double**)malloc(n*sizeof(double*));
		for(i=0; i<n; i++)
			acc[i] = &storage_acc[i*NDIM];
		*/
		for(i=0; i<n; i++){
/*
			if(fread(&mass[i], sizeof(double), 1, fptr) != 1) {
				perror("Error reading data file");
				return 3;
			}
*/
			for(j=0; j<NDIM; j++){
				if(fread(&pos[i][j], sizeof(double), 1, fptr) != 1) {
					perror("Error reading data file");
					return 3;
				}
			}
/*
			for(j=0; j<NDIM; j++){
				if(fread(&vel[i][j], sizeof(double), 1, fptr) != 1) {
					perror("Error reading data file");
					return 3;
				}
			}
			*/
		}
	
		memset(storage_acc, 0.0, n*NDIM*sizeof(double));	
	}
	printf("flag 3-%d\n",id);
	MPI_Bcast(storage_pos, n*NDIM, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	printf("flag 4\n");
	pos = (double**)malloc(n*sizeof(double*));
	for(i=0; i<n; i++)
		pos[i] = &storage_pos[i*NDIM];
	
	for(i=0; i<n; i++){
		printf("[%d]: %f\t%f\t%f", id, pos[i][0], pos[i][1], pos[i][2]);	
	}
	//run model
	//evolve(mass, pos, vel, acc, n, t, dt, t_out, dt_out, t_end, fout);

	//output elapsed time
	elapsed_time = (elapsed_time + clock()) / CLOCKS_PER_SEC;
  	//if(!id) printf("elapsed time: %lf\n", elapsed_time);
	printf("elapsed time: %lf\n", elapsed_time);
	
	if(!id){
		free(mass);
		free(pos);
		free(vel);
		free(acc);
		free(storage_pos);
		free(storage_vel);
		free(storage_acc);
	}
	MPI_Finalize();
	return 0;
}

/*
 *
 */
void evolve(double *mass, double **pos, double **vel, double **acc, 
			int n, double t, double dt, double t_out, double dt_out, double t_end, FILE* fout){
	
	int i,j,k;
	double pos_ij[NDIM];
	double r2;
	double r3;
	
	for(t=0.0; t<t_end; t += dt){
		
		//update velocity and position, reset acceleration to 0;
		for(i=0; i<n; i++){	
			for(j=0; j<NDIM; j++){
				vel[i][0] += acc[i][0]*dt/2;
				pos[i][j] += vel[i][j]*dt;
				acc[i][j] = 0.0;
			}
		}
		
		//calculate acceleration and velocity for next iteration
		for(i=0; i<n; i++){
			for(j=i+1; j<n; j++){
				r2 = 0.0;
				for(k=0; k<NDIM; k++){
					pos_ij[k] = pos[j][k] - pos[i][k];	
					r2 += pos_ij[k] * pos_ij[k];
				}
				r3 = r2 * sqrt(r2);
			
				for(k=0; k<NDIM; k++){
					acc[i][k] += mass[i]*pos_ij[k] / r3;
					acc[j][k] -= mass[j]*pos_ij[k] / r3;
					
					vel[i][k] += acc[i][k]*dt/2;
				}

			}
		}
		
		//print snapshot of simulation if appropriate time
		if(t>t_out){
			//output_snapshot(mass, pos, vel, n, t);
			t_out += dt_out;	
		}
	}
	
	output_snapshot_to_file(fout, mass, pos, vel, n, t);
}


/* allocate memory from heap */
void *my_malloc(int id, int bytes)
{
   void *buffer;
   if ((buffer = malloc ((size_t) bytes)) == NULL) {
      printf ("Error: Malloc failed for process %d\n", id);
      fflush (stdout);
      MPI_Abort (MPI_COMM_WORLD, -2);
   }
   return buffer;
}