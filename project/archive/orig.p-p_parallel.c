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

void evolve(double mass[], double pos[][NDIM], double vel[][NDIM], double acc[][NDIM], 
			int n, double t, double dt, double t_out, double dt_out, double t_end);



int main(int argc, char* argv[]){
	double elapsed_time;	
	int n = 0;				// get n count from command line
	double t = 0.0;			// assume time is zero
	double dt = 0.001;		//time step
	double t_end = 1.0;		//final time
	double t_out = 0.0;
	double dt_out = 0.1;	
	char fname[100];
	MPI_Comm comm;
	int p, id;
	
	/* initialize MPI */
 	MPI_Init(&argc, &argv);
	
	/* start couting time */
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = - MPI_Wtime();
	
	//get total num processes and process rank
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	
	if(!id){
		if(read_options(argc, argv, &n, &fname[0]))
			return 1;

		double mass[n];
		double pos[n][NDIM];
		double vel[n][NDIM];
		double acc[n][NDIM];
	}

	//parse arguments, initialize position and velocity
	//parse_input(&n, &t, mass, pos, vel, acc);

	//run model
	//evolve(mass, pos, vel, acc, n, t, dt, t_out, dt_out, t_end);

	/* final timing */
  	elapsed_time += MPI_Wtime();
  	if(!id) printf("elapsed time: %lf\n", elapsed_time);
  
  	MPI_Finalize();
	return 0;
}

/*
 *
 */
void evolve(double mass[], double pos[][NDIM], double vel[][NDIM], double acc[][NDIM], 
			int n, double t, double dt, double t_out, double dt_out, double t_end){
	
	int i,j,k;
	double pos_ij[NDIM];
	double r2;
	double r3;

	for(t=0.0; t<t_end; t += dt){
		//update velocity and position, reset acceleration to 0;
		for(i=0; i<n; i++){	
			for(j=0; j<NDIM; j++){
				vel[i][j] += acc[i][j]*dt/2;
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
			output_snapshot(mass, pos, vel, n, t);
			t_out += dt_out;	
		}
	}
}



	
	
	


