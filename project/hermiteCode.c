/*----------------------------------------------------------------------
 * usage: 
 *
 *
 *----------------------------------------------------------------------
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

const int NDIM = 3;	//Number of dimensions
const double PI = 2.0*asin(1);

int read_options(int, char* [], int*);
int parse_input(int*, double*, double[], double[][NDIM], double[][NDIM]);


int main(int argc, char* argv[]){
	
	int n = 0;		// get n count from command line
	double t = 0;	// assume time is zero
	
	printf("flag 1\n");
	if(read_options(argc, argv, &n))
		return 1;
	
	printf("flag 2\n");
	double mass[n];
	double poss[n][NDIM];
	double vel[n][NDIM];
	
	printf("flag 3\n");
	parse_input(&n, &t, mass, poss, vel);
	
	printf("flag 4\n");
	return 0;
}


int read_options(int argc, char* argv[], int* n){
	
	if(argc != 2){
		printf("usage: \n\t%s ", argv[0]);
		printf("[number of particles] \n");
		return 1;
	}
	
	*n = atoi(argv[1]);
	
	return 0;
}


int parse_input(int* n, double* t, double mass[], double poss[][NDIM], double vel[][NDIM]){
	
	scanf("%d", n);
	scanf("%lf", t);
		
	printf("n = %d\n", *n);
	printf("t = %f\n", *t);
	
	int i, j;
	
	for(i=0; i<*n; i++){
		
		scanf("%lf", &mass[i]);
		printf("mass[%d] = %f\n", i, mass[i]);
		
		for(j=0; j<NDIM; j++)
			scanf("%lf", &poss[i][j]);
		
		for(j=0; j<NDIM; j++)
			scanf("%lf", &vel[i][j]);	
		
		for(j=0; j<NDIM; j++)
			printf("poss[%d][%d] = %.16f\nvel[%d][%d] = %.16f\n",i,j,poss[i][j],i,j,vel[i][j]);
	}
	
	return 0;	
}


