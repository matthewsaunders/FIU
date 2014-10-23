#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "bmplib.h"

/*
 *
 *
 */
void usage(){
  fprintf(stderr, "usage: bmptool [-s scale | -r degree | -f ] [-o output_file] [input_file] \n");
  exit(1);
}

/*
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 *
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 */
int enlarge(PIXEL* original, int rows, int cols, int scale, 
	    PIXEL** new, int* newrows, int* newcols) 
{
  int row, col, i, j;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *newrows = scale*rows;
  *newcols = scale*cols;
  *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));

  for (row=0; row < rows; row++) {
    for(i=0; i<scale; i++){
      for (col=0; col < cols; col++) {
        for(j=0; j<scale; j++){
          PIXEL* o = original + row*cols + col;
          PIXEL* n = (*new) + row*cols*scale*scale + cols*scale*i + col*scale + col*j;
          *n = *o;
        }
      }
    }
  }

  return 0;
}

/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been read 
 * in using readFile(). The rotation is expressed in degrees and can be
 * positive, negative, or 0 -- but it must be a multiple of 90 degrees
 * 
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - a positive or negative rotation, 
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */
int rotate(PIXEL* original, int rows, int cols, int rotation,
	   PIXEL** new, int* newrows, int* newcols)
{
  if(rotation % 360 == 0){
    //do nothing
    printf("\nflag1\n");
  }
  else if((rotation > 0 && rotation % 270 == 0) || (rotation < 0 && rotation % 90 == 0 && rotation % 180 != 0 && rotation % 270 != 0)){
    printf("\nflag2\n");
  }
  else if((rotation > 0 && rotation % 180 == 0) || (rotation < 0 && rotation % 180 == 0)){
    printf("\nflag3\n");
  }

  return 0;
}

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile(). 
 * 
 * THIS IS GIVEN TO YOU SOLELY TO LOOK AT AS AN EXAMPLE
 * TRY TO UNDERSTAND HOW IT WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, PIXEL **new, int rows, int cols) 
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

int main(int argc, char *argv[])
{
  int r, c, nr, nc;
  PIXEL *b, *nb;
  char* infile;
  char* outfile;
  int fl, ro, sc, ou, nro; /* getopt flags */
  int argindex;
  int val_scale, val_rotate;

  outfile = "result.bmp";
  infile = stdin;
  argindex = 0;
  val_scale = val_rotate = 0;
  fl = ro = sc = ou = nro = 0;
  while((c = getopt(argc, argv, "srfo")) != -1){
    switch(c) {
      case 's':
        if(sc){
          fprintf(stderr, "Duplicate options\n");
          exit(-1);
        }
        sc = 1;
        break;
      case 'r':
        if(ro){
          fprintf(stderr, "Duplicate options\n");
          exit(-1);
        }
        ro = 1;
        break;
      case 'f':
        if(fl){
          fprintf(stderr, "Duplicate options\n");
          exit(-1);
        }
        printf("\noptarg: %s , sizeof: %d\n",optarg, sizeof(optarg));
        fl = 1;
        break;
      case 'o':
        if(ou){
          fprintf(stderr, "Duplicate options\n");
          exit(-1);
        }
        ou = 1;
        break;
      case '?':
        printf("\noptarg: %s , sizeof: %d\n",optarg, sizeof(optarg));

      default:
        usage();
        printf("default");
    }
  }
  argc -= optind;
  argv += optind;

  if(argc < 1){
    fprintf(stderr, "Too few arguments");
    exit(-1);
  }
/*  
  int k = 0;
  for(k=0; k<argc; k++){
    printf("arg %d: %s", k, argv[k]);
  }
*/
  /* assume if argument are true, they are in order */
  if(sc){
    val_scale = atoi(argv[argindex++]);
  }
  if(ro && !nro){
    val_rotate = atoi(argv[argindex++]);
  }
  if(ou){
    outfile = argv[argindex++];
  }
  if(argc - 1 == argindex){
    infile = argv[argindex];
  }
  
  //read input file
  readFile(infile, &r, &c, &b);

  //execute function calls based on command line flags
  if(fl){
    flip(b, &nb, r, c);
  }
  if(sc){
    enlarge(b, r, c, val_scale, &nb, &nr, &nc);
    r = nr;
    c = nc;
  }
  if(ro){
    rotate(b, r, c, val_rotate, &nb, &nr, &nc);
    r = nr;
    c = nc;
  }

  //write results to file
  writeFile(outfile, r, c, nb);
    
  free(b);
  free(nb);
  return 0;
}
