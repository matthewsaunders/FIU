#include <stdio.h>
#include <math.h>

#define dt 0.0001


int main(){

  double r[3], v[3], a[3];
  int ns, i;
  double dist;

  r[0] = 1;
  r[1] = 0;
  r[2] = 0;
  v[0] = 0;
  v[1] = 0.5;
  v[2] = 0;

  for(ns=0; ns<100000; ns++){
    //dist = sqrt(r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);
    dist = r[0]*r[0] + r[1]*r[1] + r[2]*r[2];

    for(i=0; i<3; i++){
      a[i] = -r[i] / (dist*sqrt(dist));
    }
    
    for(i=0; i<3; i++){
      r[i] += v[i]*dt;
      v[i] += a[i]*dt;
    }

    printf("%f %f %f\t", r[0], r[1], r[2]);
    printf("%f %f %f\n", v[0], v[1], v[2]);
  }

  return 0;
}
