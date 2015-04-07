/*-----------------------------------------------------------------------
 *
 * usage: ./generateParticles [number of particles] 
 *							[seed for random number generator]
 *
 * The number of particles has to be specified since there is no default 
 * value.  If no seed is specified for the random number generator, a
 * random value is chosen based on the clock time.
 *
 * Example: "./generateParticles 3 > data.out" will produce a file in
 * the following format where m is mass, p is possition, and v is 
 * velocity:
 *
 *		3
 *		0
 *		m1 p1_x p1_y p1_z v1_x v1_y v1_z
 *		m1 p2_x p2_y p2_z v2_x v2_y v2_z
 *		m1 p3_x p3_y p3_z v3_x v3_y v3_z
 *
 *-----------------------------------------------------------------------
 *
 * Particles are created in a sphere with unit radius and constant 
 * density. The total mass is unity so each particle will have mass 1/N,
 * for N particles in total.  Each particle will be located randomly 
 * within the unit sphere, with initial velocity of zero. 
 *
 *----------------------------------------------------------------------
 *
 * version 1:	07 Apr 2015		M. Saunders
 *
 *----------------------------------------------------------------------
 */
#include <stdio.h>
#include <math.h>		// for asin(), pow()
#include <stdlib.h>		// for atoi()
#include <string.h>		
#include <unistd.h>		//
#include <time.h>		// for time()

const int NDIM = 3;	//Number of dimensions
const double PI = 2.0*asin(1);

//function prototypes
int read_options(int, char*[], int*, int*);
double randunit(double);
double rand_number(double, double);
void populate_data(double[], double[][NDIM], double[][NDIM], int);
void output_snapshot(double[], double[][NDIM], double[][NDIM], int);

/*----------------------------------------------------------------------
 * main -- read in option, generate sphere of particles for model
 *----------------------------------------------------------------------
 */
int main(int argc, char* argv[]){
	int n = 0;
	int seed = 0;
	
	if(!read_options(argc, argv, &n, &seed))
		return 1;
	
	double mass[n];
	double poss[n][NDIM];
	double vel[n][NDIM];

	populate_data(mass, poss, vel, n);
	output_snapshot(mass, poss, vel, n);
	
	return 0;
}

/*----------------------------------------------------------------------
 * read_options -- read command line arguments and set them.
 *
 * To initialize the random number generator, invoke this script with
 * a nonzero seed. To run with actual random numbers, invoke with seed
 * value of 0.
 *----------------------------------------------------------------------
 */
int read_options(int argc, char* argv[], int* n, int* seed){
	
	if(argc < 2){
		printf("usage: \n\t%s ", argv[0]);
		printf("[number of particles] ");
		printf("[seed for random number generator]\n");
		return 1;
	}
	
	*n = atoi(argv[1]);
	if(*n < 1){
		printf("ERROR: A value of N = %d is not allowed.\n", *n);	
		return 1;
	}
	
	if(argc == 3)
		*seed = atoi(argv[2]);		
	else
		*seed = time(0);	
	
	return 1;
}

/*----------------------------------------------------------------------
 * randunit -- returns a random double number within the unit interval.
 *
 * Based on the berkeley rand.c
 *
 * To initialize the random number generator, invoke with a nonzero 
 * argument, which will become the seed.  To run with random numbers, 
 * invoke with 0.
 *----------------------------------------------------------------------
 */
double randunit(double seed){
	const double MAXN = 2147483647;
	
	static int randx;
	
	if(seed){
		randx = seed;
		return 0.0;
	}
		
	return ((double)((randx = randx * 1103515245 + 12345) & 0x7FFFFFFF) / MAXN);
}

/*----------------------------------------------------------------------
 * rand_numebr -- returns a random double within interval [a,b] by 
 * invoking randunit().
 *----------------------------------------------------------------------
 */
double rand_number(double a, double b){
	return (a +(b-a)*randunit(0));
}

/*----------------------------------------------------------------------
 * populate_data -- construct a unit sphere with homogeneous density of
 * particles whose total mass is unity.  Each particles inital velocity
 * is zero.
 *
 * 
 *----------------------------------------------------------------------
 */
void populate_data(double mass[], double pos[][NDIM], double vel[][NDIM], int n){
	
	int i,j;
	double r;
	double theta;
	double phi;
	
	
	for(i=0; i<n; i++)
		mass[i] = 1.0 / (double)n;

	for(i=0; i<n; i++){		
		r = pow(rand_number(0.0, 1.0), 1.0/3.0);
		theta = rand_number(0.0, PI);
		phi = rand_number(0.0, 2*PI);
		
		pos[i][0] = r*sin(theta)*cos(phi);
		pos[i][1] = r*sin(theta)*sin(phi);
		pos[i][2] = r*cos(theta);
		
		/*
		printf("\n\nr = %f\n", r);
		printf("theta = %f\n", theta);
		printf("phi = %f\n", phi);
		printf("poss[%d][0] = %f\n",i, pos[i][0]);
		printf("poss[%d][1] = %f\n",i, pos[i][1]);
		printf("poss[%d][2] = %f\n",i, pos[i][2]);
		*/
		
		for(j=0; j<NDIM; j++)
			vel[i][j] = 0;
		
	}	
				
}

/*----------------------------------------------------------------------
 * output_snapshot -- Write a single snapshot to stdout. In this case, 
 * the snapshot is the inital snapshot (when t=0).
 *----------------------------------------------------------------------
 */
void output_snapshot(double mass[], double pos[][NDIM], double vel[][NDIM], int n){

	int i,j;
	
	printf("%d\n", n);
	printf("%d\n", 0);
	
	for(i=0; i<n; i++){
		printf("%.16f ", mass[i]);
		
		for(j=0; j<NDIM; j++)
			printf("%.16f ", pos[i][j]);
		
		for(j=0; j<NDIM; j++)
			printf("%.16f ", vel[i][j]);

		printf("\n");
	}
}

/*----------------------------------------------------------------------
 *
 * EOF: 	generateParticles.c
 *
 *----------------------------------------------------------------------
 */