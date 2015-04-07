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
	
	if(read_options(argc, argv, &n))
		return 1;
	
	double mass[n];
	double poss[n][NDIM];
	double vel[n][NDIM];
	
	parse_input(&n, &t, mass, poss, vel);
	
	return 0;
}


int get_options(int argc, char* argv[], int* n){
	
	if(argc != 2){
		printf("usage: \n\t%s ", argv[0]);
		printf("[number of particles] \n");
		return 1;
	}
	
	*n = atoi(argv[1]);
	
	return 0;
}


int parse_intput(int* n, double* t, double mass[], double poss[][NDIM], double vel[][NDIM]){
	
	return 0;	
}


