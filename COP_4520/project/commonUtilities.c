#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utilities.h"

/*
 *
 *
 */
int read_options(int argc, char* argv[], int* n, char* fname){
	
	if(argc < 2 || argc > 3){
		printf("usage: \n\t%s ", argv[0]);
		printf("[number of particles] \n");
		return 1;
	}
	
	*n = atoi(argv[1]);
	
	if(argc == 3){
		strcpy(fname, argv[2]);
	}
	
	return 0;
}

/*
 *
 *
 */
int parse_input(FILE* fptr, int* n, double* t, double *mass, double **pos, double **vel, double **acc, double *storage_pos, double *storage_vel, double *storage_acc){

	int i,j;
	
	if(fread(n, sizeof(int), 1, fptr) != 1 || fread(t, sizeof(double), 1, fptr) != 1) {
    	perror("Error reading data file");
    	return 3;
  	}
	printf("N: %d\nt: %f\n", *n, *t);
	
	mass = (double*)malloc((*n)*sizeof(double));
	
	storage_pos = malloc((*n)*NDIM*sizeof(double));
	pos = (double**)malloc((*n)*sizeof(double*));
	for(i=0; i<(*n); i++)
		pos[i] = &storage_pos[i*NDIM];

	storage_vel = malloc((*n)*NDIM*sizeof(double));
	vel = (double**)malloc((*n)*sizeof(double*));
	for(i=0; i<(*n); i++)
		vel[i] = &storage_vel[i*NDIM];
	
	storage_acc = malloc((*n)*NDIM*sizeof(double));
	acc = (double**)malloc((*n)*sizeof(double*));
	for(i=0; i<(*n); i++)
		acc[i] = &storage_acc[i*NDIM];
	
	for(i=0; i<(*n); i++){
		
			printf("%d: ",i);
			if(fread(&mass[i], sizeof(double), 1, fptr) != 1) {
				perror("Error reading data file");
				return 3;
			}
			printf("%10.8f\t", mass[i]);
		
			for(j=0; j<NDIM; j++){
				if(fread(&pos[i][j], sizeof(double), 1, fptr) != 1) {
					perror("Error reading data file");
					return 3;
				}
				printf("%10.8f\t", pos[i][j]);
			}
		
			for(j=0; j<NDIM; j++){
				if(fread(&vel[i][j], sizeof(double), 1, fptr) != 1) {
					perror("Error reading data file");
					return 3;
				}
				printf("%10.8f\t", vel[i][j]);
			}
		
			printf("\n");
		}

	
	memset(storage_acc, 0.0, (*n)*NDIM*sizeof(double));
	return 0;
}

/*
 *
 *
 */
void output_snapshot(double *mass, double **pos, double **vel, int n, double t){

	int i;
	
	printf("%d\n", n);
	printf("%f\n", t);
	
	for(i=0; i<n; i++){
		printf("%.16f ", mass[i]);
		printf("%.16f\t %.16f\t %.16f\t", pos[i][0], pos[i][1], pos[i][2]);
		printf("%.16f\t %.16f\t %.16f\t", vel[i][0], vel[i][1], vel[i][2]);
		printf("\n");
	}
}

/*
 *
 *
 */
void output_snapshot_to_file(FILE* fptr, double *mass, double **pos, double **vel, int n, double t){
	int i,j;
	
	fwrite (&n, sizeof(int), 1, fptr);
	fwrite (&t, sizeof(double), 1, fptr);
	
	for(i=0; i<n; i++){
		fwrite (&mass[i], sizeof(double), 1, fptr);
		
		for(j=0; j<NDIM; j++){
			fwrite (&pos[i][j], sizeof(double), 1, fptr);
		}
		
		for(j=0; j<NDIM; j++){
			fwrite (&vel[i][j], sizeof(double), 1, fptr);
		}
	}
}



