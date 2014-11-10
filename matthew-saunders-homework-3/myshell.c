/* This example is stolen from Dr. Raju Rangaswami's original 4338
   demo and modified to fit into our lecture. */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_ARGS 20
#define BUFFSIZ 1024

int get_args(char* cmdline, char* args[]) 
{
  int i = 0;

  /* if no args */
  if((args[0] = strtok(cmdline, "\n\t ")) == NULL) 
    return 0; 

  while((args[++i] = strtok(NULL, "\n\t ")) != NULL) {
    if(i >= MAX_ARGS) {
      printf("Too many arguments!\n");
      exit(1);
    }
  }
  /* the last one is always NULL */
  return i;
}

void execute(char* cmdline) 
{
  int pid, async, index;
  char* args[MAX_ARGS];
  char oflag, aflag, iflag, pflag;
  oflag = aflag = iflag = pflag = 0;
  
  char* ofile;
  char* ifile;
  char* args_copy[MAX_ARGS];
  int ofile_no, ifile_no;
  FILE *outfp, *infp;

  memset(args_copy, 0, sizeof(args_copy));

  //Get the number of arguments
  int nargs = get_args(cmdline, args);
  if(nargs <= 0) return;

  //Check if user wants to exit shell
  if(!strcmp(args[0], "quit") || !strcmp(args[0], "exit")) {
    exit(0);
  }

  /* check if async call */
  if(!strcmp(args[nargs-1], "&")) { async = 1; args[--nargs] = 0; }
  else async = 0;

    index = 0;
   
    //Cycle through arguments until a shell redirect is found
    //while((index < nargs) && (strcmp(args[index], ">") || strcmp(args[index], ">>"))){ 
    while((index < nargs) && strcmp(args[index], ">") && strcmp(args[index], ">>") && strcmp(args[index], "<") ){ 
      args_copy[index] = args[index];
      printf("arg%d: %s\n",index,args[index]);
      index++; }

    //Check if output is being rerouted
    if(index < nargs){
      if(!strcmp(args[index], ">") || !strcmp(args[index], ">>")){
        if(!strcmp(args[index], ">")){
          printf("change output\n");
          oflag = 1;
        }

        if(!strcmp(args[index], ">>")){
          printf("append output\n");
          aflag = 1;
        }
        ofile = args[index + 1];
        index += 2;
      }

      if(!strcmp(args[index], "<")){
        printf("change input\n");
        iflag = 1;
        ifile = args[index + 1];
        index += 2;
      }

    }


  pid = fork();
  if(pid == 0) { /* child process */
    
    //output is redirected
    if(oflag){
      if ((outfp = fopen(ofile, "w")) == NULL) {
        return;
      } else {
        ofile_no = fileno(outfp);
        dup2(ofile_no, STDOUT_FILENO);        
      }
    }

    //output is appended
    if(aflag){
      if ((outfp = fopen(ofile, "a")) == NULL) {
        return;
      } else {
        ofile_no = fileno(outfp);
        dup2(ofile_no, STDOUT_FILENO);
      }
    }

    //input is redirected
    if(iflag){
      if ((infp = fopen(ifile, "r")) == NULL) {
        return;
      } else {
        ofile_no = fileno(infp);
        dup2(ifile_no, STDIN_FILENO);
      }
    }


    execvp(args_copy[0], args_copy);
    /* return only when exec fails */
    perror("exec failed");
    exit(-1);
  } else if(pid > 0) { /* parent process */
    if(!async) waitpid(pid, NULL, 0);
    else printf("this is an async call\n");
  } else { /* error occurred */
    perror("fork failed");
    exit(1);
  } 

 
  //} //end while(nargs > 0)
}

int main (int argc, char* argv [])
{
  char cmdline[BUFSIZ];
  
  for(;;) {
    printf("assign4$ ");
    if(fgets(cmdline, BUFSIZ, stdin) == NULL) {
      perror("fgets failed");
      exit(1);
    }
    execute(cmdline) ;
  }
  return 0;
}
