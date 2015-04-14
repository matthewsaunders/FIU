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
int parse_input(int*, double*, double[], double[][NDIM], double[][NDIM], double[][NDIM]);
void output_snapshot(double[], double[][NDIM], double[][NDIM], int, double);

#endif