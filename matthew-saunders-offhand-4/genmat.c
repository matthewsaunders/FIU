#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

int main (int argc, char * argv[]) 
{
  int i, j;
  int m, n;
  FILE *foutptr;
  float *a;
  float *ptr;
  struct timeval tp;
  
  if(argc != 4) {
    printf("Usage: %s rows columns filename\n", argv[0]);
    return 1;
  }

  m = atoi(argv[1]);
  n = atoi(argv[2]);
  if(m <= 0 || n <= 0) {
    printf("ERROR: wrong dimensions: rows=%d, columns=%d\n", m, n);
    return 2;
  }

  foutptr = fopen (argv[3], "w");
  if(!foutptr) {
    perror("ERROR: can't open output file\n");
    return 3;
  }

  fwrite (&m, sizeof(int), 1, foutptr);
  fwrite (&n, sizeof(int), 1, foutptr);

  gettimeofday(&tp, NULL);
  srand((int)tp.tv_usec);
  
  a = (float*)malloc(n*sizeof(float));
  for (i = 0; i < m; i++) {
    ptr = a;
    for (j = 0; j < n; j++) {
      *(ptr++) = ((float)rand())/RAND_MAX;
    }
    fwrite (a, sizeof(float), n, foutptr);
  }

  free(a);
  fclose (foutptr);
  return 0;
}
