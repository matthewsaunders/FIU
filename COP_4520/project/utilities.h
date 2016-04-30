#define NDIM 3	//Number of dimensions
#define PI 3.1415962  //PI 2.0*asin(1)

#ifndef COMMON_UTILITIES_H
#define COMMON_UTILITIES_H

#include <stdio.h>
typedef struct{
	double mass;
	double pos_x;
	double pos_y;
	double pos_z;
	double vel_x;
	double vel_y;
	double vel_z;	
} particle;

int read_options(int, char* [], int*, char*);
int parse_input(FILE* fptr, int* n, double* t, double *mass, double **pos, double **vel, double **acc, double *storage_pos, double *storage_vel, double *storage_acc);
void output_snapshot(double*, double**, double**, int, double);
void output_snapshot_to_file(FILE* fptr, double *mass, double **pos, double **vel, int n, double t);
#endif