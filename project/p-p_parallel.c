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
#include "utilities.h"

void evolve(double *mass, double **pos, double **vel, double **acc, 
			int n, double t, double dt, double t_out, double dt_out, double t_end, FILE* fout);
void* work(void* arg);

/* block decomposition macros */
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n)+1)
#define BLOCK_OWNER(j,p,n) (((p)*((j)+1)-1)/(n))

struct mythread {
  pthread_t id; /* thread id */
  int idx; /*  */
  int low; /*  */
  int high; /*  */
  int size; /*  */
};

double *mass;
double **pos, **vel, **acc;
double *storage_pos, *storage_vel, *storage_acc;
	double t = 0.0;			// assume time is zero
	double dt = 0.001;		//time step
	double t_end = 1.0;		//final time
int n = 0;

int main(int argc, char* argv[]){
	double elapsed_time;
	int p;
	

	double t_out = 0.0;
	double dt_out = 0.1;	
	struct mythread* th;
	FILE* fptr;
	FILE* fout;
	elapsed_time = - clock();
	
	if(argc != 4){
		printf("usage: \n\t%s ", argv[0]);
		printf("[# threads] [input file] [output file]\n");
		return 1;
	}
	
	if( (p = atoi(argv[1])) < 0){
		perror("ERROR: number of processes must be positive\n");
    	return 2;
	}
	
	if( !(fptr = fopen (argv[2], "r")) ) {
    	perror("ERROR: can't open data file\n");
    	return 2;
  	}
	
	if( !(fout = fopen (argv[3], "w")) ) {
    	perror("ERROR: can't open data file\n");
    	return 2;
  	}
	
	int i,j;
	

	/* parse arguments, initialize position and velocity */
	if(fread(&n, sizeof(int), 1, fptr) != 1 || fread(&t, sizeof(double), 1, fptr) != 1) {
    	perror("Error reading data file");
    	return 3;
  	}
	printf("N: %d\nt: %f\n", n, t);
	
	mass = (double*)malloc(n*sizeof(double));
	
	storage_pos = malloc(n*NDIM*sizeof(double));
	pos = (double**)malloc(n*sizeof(double*));
	for(i=0; i<n; i++)
		pos[i] = &storage_pos[i*NDIM];

	storage_vel = malloc(n*NDIM*sizeof(double));
	vel = (double**)malloc(n*sizeof(double*));
	for(i=0; i<n; i++)
		vel[i] = &storage_vel[i*NDIM];
	
	storage_acc = malloc(n*NDIM*sizeof(double));
	acc = (double**)malloc(n*sizeof(double*));
	for(i=0; i<n; i++)
		acc[i] = &storage_acc[i*NDIM];
	
	for(i=0; i<n; i++){
			if(fread(&mass[i], sizeof(double), 1, fptr) != 1) {
				perror("Error reading data file");
				return 3;
			}

			for(j=0; j<NDIM; j++){
				if(fread(&pos[i][j], sizeof(double), 1, fptr) != 1) {
					perror("Error reading data file");
					return 3;
				}
			}
		
			for(j=0; j<NDIM; j++){
				if(fread(&vel[i][j], sizeof(double), 1, fptr) != 1) {
					perror("Error reading data file");
					return 3;
				}
			}
		}

	
	memset(storage_acc, 0.0, n*NDIM*sizeof(double));

	th = (struct mythread*)malloc(p*sizeof(struct mythread));
	for(i=0; i<p; i++) {
		th[i].low = BLOCK_LOW(i, p, n); 
		th[i].high = BLOCK_HIGH(i, p, n); 
		th[i].idx = i;
		th[i].size = BLOCK_SIZE(i, p, n);;
		pthread_create(&th[i].id, 0, work, &th[i]);
	}
	
	for(i=0; i<p; i++) {
		pthread_join(th[i].id, 0);
	}

	output_snapshot_to_file(fout, mass, pos, vel, n, t);
	
	//output elapsed time
	elapsed_time = (elapsed_time + clock()) / CLOCKS_PER_SEC;
	printf("elapsed time: %lf\n", elapsed_time);
	
	return 0;
}

void* work(void* arg)
{
  	struct mythread* myt = (struct mythread*)arg;
  	printf("[%d]: %d %d %d\n", myt->idx, myt->low, myt->high, myt->size);
	
	int i,j,k;
	double pos_ij[NDIM];
	double r2;
	double r3;
	
	//initialize submatrix
	double *my_mass;
	double *my_storage_pos, *my_storage_vel, *my_storage_acc;
	double **my_pos, **my_vel, **my_acc;
	
	//allocate submatrix specific to this process	
	my_storage_pos = malloc(myt->size*NDIM*sizeof(double));
	memcpy(my_storage_pos, storage_pos + (myt->low*NDIM), myt->size*NDIM*sizeof(double));
	my_pos = (double**)malloc(myt->size*sizeof(double*));
	for(i=0; i<myt->size; i++)
		my_pos[i] = &my_storage_pos[i*NDIM];
	
	my_storage_vel = malloc(myt->size*NDIM*sizeof(double));
	memcpy(my_storage_vel, storage_vel + (myt->low*NDIM), myt->size*NDIM*sizeof(double));
	my_vel = (double**)malloc(myt->size*sizeof(double*));
	for(i=0; i<myt->size; i++)
		my_vel[i] = &my_storage_vel[i*NDIM];
	
	my_storage_acc = malloc(myt->size*NDIM*sizeof(double));
	memcpy(my_storage_acc, storage_acc + (myt->low*NDIM), myt->size*NDIM*sizeof(double));
	my_acc = (double**)malloc(myt->size*sizeof(double*));
	for(i=0; i<myt->size; i++)
		my_acc[i] = &my_storage_acc[i*NDIM];
	
	
	for(t=0.0; t<t_end; t += dt){
		//update velocity and position, reset acceleration to 0;
		for(i=myt->low; i<myt->size; i++){	
			for(j=0; j<NDIM; j++){
				my_vel[i][0] += acc[i][0]*dt/2;
				my_pos[i][j] += vel[i][j]*dt;
				my_acc[i][j] = 0.0;
			}
		}
		
		memcpy(storage_pos + (myt->low*NDIM), my_storage_pos, myt->size*NDIM*sizeof(double));
		memcpy(storage_vel + (myt->low*NDIM), my_storage_vel, myt->size*NDIM*sizeof(double));
		memcpy(storage_acc + (myt->low*NDIM), my_storage_acc, myt->size*NDIM*sizeof(double));
		
		//calculate acceleration and velocity for next iteration
		for(i=myt->low; i<myt->size; i++){
			for(j=i+1; j<n; j++){
				r2 = 0.0;
				for(k=0; k<NDIM; k++){
					pos_ij[k] = pos[j][k] - pos[i][k];	
					r2 += pos_ij[k] * pos_ij[k];
				}
				r3 = r2 * sqrt(r2);
			
				for(k=0; k<NDIM; k++){
					my_acc[i][k] += mass[i]*pos_ij[k] / r3;
					//acc[j][k] -= mass[j]*pos_ij[k] / r3;
					
					my_vel[i][k] += my_acc[i][k]*dt/2;
				}

			}
		}
		
		memcpy(storage_pos + (myt->low*NDIM), my_storage_pos, myt->size*NDIM*sizeof(double));
		memcpy(storage_vel + (myt->low*NDIM), my_storage_vel, myt->size*NDIM*sizeof(double));
		memcpy(storage_acc + (myt->low*NDIM), my_storage_acc, myt->size*NDIM*sizeof(double));
	}
	
  	return 0;
}

/*
 *
 */
void evolve_step(double *mass, double **pos, double **vel, double **acc, 
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
			output_snapshot(mass, pos, vel, n, t);
			t_out += dt_out;	
		}
	}
	
	output_snapshot_to_file(fout, mass, pos, vel, n, t);
}


