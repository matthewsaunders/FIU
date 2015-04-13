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


/*
 *
 */
void initial_energy(double mass[], double pos[][NDIM], double vel[][NDIM], int n, 
					  double t, double dt, double t_final){
	
	fprintf(stderr, "Starting Experiment...\n\n");
	fprintf(stderr, "Number of bodies: %d\n", n);
	fprintf(stderr, "Time step size: %f\n", dt);
	fprintf(stderr, "Time interval: %f - %f\n\n", t, t_final);
	
}

/*
 *
 */
void calculate_energy(double mass[], double pos[][NDIM], double vel[][NDIM], int n, 
					  double t, double dt, int num_steps){
	
	int i,j;
	double E_kin, E_pot, E_tot;
	
	E_kin = E_pot = 0.0;
	
	for(i=0; i<n; i++)
		for(j=0; j<NDIM; j++)
			E_kin += 0.5*mass[i] + vel[i][j]*vel[i][j];
	
	E_tot = E_kin + E_pot;
	
	fprintf(stderr, "Time t = %f:\n", t);
	fprintf(stderr, "\tstep = %d:\n", num_steps);
	fprintf(stderr, "\tE_kin = %f:\n", E_kin);
	fprintf(stderr, "\tE_pot = %f:\n", E_pot);
	fprintf(stderr, "\tE_tot = %f:\n", E_tot);
	//fprintf(stderr, );
	
}




