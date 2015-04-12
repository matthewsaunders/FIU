#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "utilities.h"

//const int NDIM = 3;	//Number of dimensions
//const double PI = 2.0*asin(1);

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
int parse_input(int* n, double* t, double mass[], double pos[][NDIM], double vel[][NDIM]){
	
	scanf("%d", n);
	scanf("%lf", t);
	
	int i;
	
	for(i=0; i<*n; i++){
		scanf("%lf", &mass[i]);
		scanf("%lf %lf %lf", &pos[i][0], &pos[i][1], &pos[i][2]);	
		scanf("%lf %lf %lf", &vel[i][0], &vel[i][1], &vel[i][2]);
	}
	return 0;	
}

/*
 *
 *
 */
void output_snapshot(double mass[], double pos[][NDIM], double vel[][NDIM], int n, double t){

	int i;
	
	printf("%d\n", n);
	printf("%f\n", t);
	
	for(i=0; i<n; i++){
		printf("%.16f ", mass[i]);
		printf("%.16f %.16f %.16f", pos[i][0], pos[i][1], pos[i][2]);
		printf("%.16f %.16f %.16f", vel[i][0], vel[i][1], vel[i][2]);
		printf("\n");
	}
}







