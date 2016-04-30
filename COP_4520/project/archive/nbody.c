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
#include "utilities_nbody.h"

int n = 0;		// get n count from command line
double t = 0;	// assume time is zero
double dt = 0.001;	//time step
double t_final = 10;	//final time
double t_output;
double dt_output = 0.1;
char fname[100];
int num_steps = 0;


int main(int argc, char* argv[]){
	
	printf("flag 00");
	particle* universe = (particle*)NULL;
	
	printf("flag 0");
	//get command line arguments
	if(read_options(argc, argv, &n, &fname[0]))
		return 1;
	
	printf("flag 1");
	//construct universe as array of type particle
	universe = construct_universe(n);
	populate_universe(&n, &t, universe);
	
	printf("flag 2");
	
	
	/*
	for(;;){
		while(t < t_output && t < t_final){
			//step_forward(mass, pos, vel, acc, jerk, n, t, dt, epot, coll_time);
			num_steps++;
		}
		if(t >= t_output){
			//output_snapshot(mass, pos, vel, n, t);
			t_output += dt_output;
		}
		if(t >= t_final)
			break;
	}
	*/
	
	
	
	return 0;
}























