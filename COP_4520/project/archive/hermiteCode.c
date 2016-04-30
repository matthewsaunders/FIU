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

void evolve(double mass[], double pos[][NDIM], double vel[][NDIM], int n, 
			double t, double dt, double dt_out);
void evolve_step(double mass[], double pos[][NDIM], double vel[][NDIM],
				double acc[][NDIM], double jerk[][NDIM], int n, double* t,
				double dt, double* coll_time);
void predict_step(double pos[][NDIM], double vel[][NDIM], double acc[][NDIM], 
				  double jerk[][NDIM], int n, double dt);
void correct_step(double pos[][NDIM], double vel[][NDIM], double acc[][NDIM], double jerk[][NDIM], 
				  double old_pos[][NDIM], double old_vel[][NDIM], double old_acc[][NDIM], double old_jerk[][NDIM],
				  int n, double dt);

int main(int argc, char* argv[]){
	
	int n = 0;		// get n count from command line
	double t = 0;	// assume time is zero
	double dt = 0.001;	//time step
	double t_final = 10;	//final time
	double dt_output = 0.1;
	char fname[100];
	int num_steps = 0;
	
	if(read_options(argc, argv, &n, &fname[0]))
		return 1;
	
	double mass[n];
	double pos[n][NDIM];
	double vel[n][NDIM];
	
	parse_input(&n, &t, mass, pos, vel);
	
	
	
	
	return 0;
	
}


void evolve(double mass[], double pos[][NDIM], double vel[][NDIM], int n, double t, double dt, double dt_out){
	
	double acc[n][NDIM];
	double jerk[n][NDIM];
	double coll_time;
	
	//get_acc_jerk_coll();
	
	int num_steps = 0;
	
	if(t==0.0)
		output_snapshot(mass, pos, vel, n, t);
	
	double t_out = t + dt_out;
	double t_end = t + dt;
	
	
	
	for(;;){
		while(t < t_out && t < t_end){
			evolve_step(mass, pos, vel, acc, jerk, n, &t, dt, &coll_time);
			num_steps++;
		}
		if(t >= t_out){
			output_snapshot(mass, pos, vel, n, t);
			t_out += dt_out;
		}
		if(t >= t_end)
			break;
	}
	
}


void evolve_step(double mass[], double pos[][NDIM], double vel[][NDIM],
				double acc[][NDIM], double jerk[][NDIM], int n, double* t,
				double dt, double* coll_time){
	
	double old_pos[n][NDIM];	
	double old_vel[n][NDIM];
	double old_acc[n][NDIM];
	double old_jerk[n][NDIM];
	
	int i,j;
	
	for(i=0; i<n; i++)
		for(j=0; j<NDIM; j++){
			old_pos[i][j] = pos[i][j];	
			old_vel[i][j] = vel[i][j];
			old_acc[i][j] = acc[i][j];
			old_jerk[i][j] = jerk[i][j];
		}
	
	predict_step(pos, vel, acc, jerk, n, dt);
	//get_acc_jerk_coll();
	correct_step(pos, vel, acc, jerk, old_pos, old_vel, old_acc, old_jerk, n, dt);
	
	*t += dt;
}


void predict_step(double pos[][NDIM], double vel[][NDIM], double acc[][NDIM], 
				  double jerk[][NDIM], int n, double dt){

	int i,j;
	
	for(i=0; i<n; i++)
		for(j=0; j<NDIM; j++){
			pos[i][j] += vel[i][j]*dt + acc[i][j]*dt*dt/2 + jerk[i][j]*dt*dt*dt/6;
			vel[i][j] += acc[i][j]*dt + jerk[i][j]*dt*dt/2;
		}
}

void correct_step(double pos[][NDIM], double vel[][NDIM], double acc[][NDIM], double jerk[][NDIM], 
				  double old_pos[][NDIM], double old_vel[][NDIM], double old_acc[][NDIM], double old_jerk[][NDIM],
				  int n, double dt){
	
	int i,j;
	
	for(i=0; i<n; i++)
		for(j=0; j< NDIM; j++){
			vel[i][j] = old_vel[i][j] + (old_acc[i][j] + acc[i][j])*dt/2 + (old_jerk[i][j] - jerk[i][j])*dt*dt/12;
			pos[i][j] = old_pos[i][j] + (old_vel[i][j] + vel[i][j])*dt/2 + (old_acc[i][j] - acc[i][j])*dt*dt/12;
		}
	
}
	

void get_acc_jerk_coll(){
	
	int i, j, k;
	
	for(i=0; i<n; i++)
		for(j=0; j<NDIM; j++)
			acc[i][j] = jerk[i][j] = 0;
	
	double LARGE_NUM = 1e300;
	double colle_time_q = LARGE_NUM;
	double coll_est_q;
	
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			double rji[NDIM];
			double vji[NDIM];
	
			for(k=0; k<NDIM; k++){
				rji[k] = pos[j][k] - pos[i][k];
				vji[k] = [vel[j][k] - vel[i][k];
			}
	
	
	
	
		}
	}
	
	
	
	
}
	
	
	


