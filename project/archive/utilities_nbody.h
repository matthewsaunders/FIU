#define NDIM 3	//Number of dimensions
#define PI 3.1415962  //PI 2.0*asin(1)

#ifndef COMMON_UTILITIES_H
#define COMMON_UTILITIES_H

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
int parse_input(int*, double*, double[], double[][NDIM], double[][NDIM]);
void output_snapshot(double[], double[][NDIM], double[][NDIM], int, double);
void initial_energy(double mass[], double pos[][NDIM], double vel[][NDIM], int n, 
					  double t, double dt, double t_final);
void calculate_energy(double mass[], double pos[][NDIM], double vel[][NDIM], int n, 
					  double t, double dt, int num_steps);

particle* construct_universe(int);
void populate_universe(int* n, double* t, particle* universe);








#endif