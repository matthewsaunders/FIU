/*----------------------------------------------------------------------
 * usage: 
 * $ cat out | ./hermiteCode 10000 2>&1
 *
 *----------------------------------------------------------------------
 */
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
int read_options(int, char* [], int*, char*);
int parse_input(int*, double*, double[], double[][NDIM], double[][NDIM]);
void output_snapshot(double[], double[][NDIM], double[][NDIM], int, double);
*/
int main(int argc, char* argv[]){
	
	int n = 0;		// get n count from command line
	double t = 0;	// assume time is zero
	double dt = 0.001;	//time step
	double t_final = 10;	//final time
	double t_energy;
	double t_output;
	double dt_energy = 1.0;
	double dt_output = 0.1;
	char fname[100];
	int num_steps = 0;
	
	if(read_options(argc, argv, &n, &fname[0]))
		return 1;
	
	double mass[n];
	double pos[n][NDIM];
	double vel[n][NDIM];
	
	parse_input(&n, &t, mass, pos, vel);
	
	
	//initial_energy(mass, pos, vel, n, t, dt, t_final);
	
	//calculate_energy(mass, pos, vel, n, t, dt, num_steps);
	
	//initial output
	output_snapshot(mass, pos, vel, n, t);
	t_output = t + dt_output;
	
	for(;;){
		while(t < t_output && t < t_final){
			//step_forward(mass, pos, vel, acc, jerk, n, t, dt, epot, coll_time);
			num_steps++;
		}
		if(t >= t_output){
			output_snapshot(mass, pos, vel, n, t);
			t_output += dt_output;
		}
		if(t >= t_final)
			break;
	}
	
	
	
	
	return 0;
}























