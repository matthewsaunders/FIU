#include <stdio.h>
#include <math.h>		// for asin(), pow()
#include <stdlib.h>		// for atoi()
#include <string.h>		
#include <unistd.h>		//
#include <time.h>		// for time()

const int NDIM = 3;	//Number of dimensions

int print_snapshot(FILE*);

/*----------------------------------------------------------------------
 * main -- read in option, generate sphere of particles for model
 *----------------------------------------------------------------------
 */
int main(int argc, char* argv[]){
	FILE *fptr;
	
	if(argc != 2){
		printf("usage: \n\t%s ", argv[0]);
		printf("[number of particles] [output file] ");
		printf("[seed for random number generator]\n");
		return 1;
	}
	
 	if( !(fptr = fopen (argv[1], "r")) ) {
    	perror("ERROR: can't open data file\n");
    	return 2;
  	}
	
	print_snapshot(fptr);
	
	fclose(fptr);
	return 0;
}

/*
 *
 */
int print_snapshot(FILE* fptr){
	int i,j;
	int n;
	double t = 0.0;
	double ptr;
	
	if(fread(&n, sizeof(int), 1, fptr) != 1 || fread(&t, sizeof(double), 1, fptr) != 1) {
    	perror("Error reading data file");
    	return 3;
  	}
	printf("N: %d\nt: %f\n", n, t);
	
	printf("mass\t\tposition\t\t\t\t\t\t\t\tvelocity\n");
	printf("-------\t\t-----------------\t\t\t\t\t\t\t----------------------\n");
	for(i=0; i<n; i++){
		
		if(fread(&ptr, sizeof(double), 1, fptr) != 1) {
			perror("Error reading data file");
			return 3;
		}
		printf("%10.8f\t", ptr);
		
		for(j=0; j<NDIM; j++){
			if(fread(&ptr, sizeof(double), 1, fptr) != 1) {
				perror("Error reading data file");
				return 3;
			}
			printf("%16.12f\t", ptr);
		}
		
		for(j=0; j<NDIM; j++){
			if(fread(&ptr, sizeof(double), 1, fptr) != 1) {
				perror("Error reading data file");
				return 3;
			}
			printf("%16.12f\t", ptr);
		}
		printf("\n");
	}
	
	return 0;
}
