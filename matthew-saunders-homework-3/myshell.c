/* This example is stolen from Dr. Raju Rangaswami's original 4338
   demo and modified to fit into our lecture. */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARGS 20
#define BUFSIZ 1024

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
  int pid, async;
  char* args[MAX_ARGS];

  int nargs = get_args(cmdline, args);
  if(nargs <= 0) return;

  if(!strcmp(args[0], "quit") || !strcmp(args[0], "exit")) {
    exit(0);
  }

  /* check if async call */
  if(!strcmp(args[nargs-1], "&")) { async = 1; args[--nargs] = 0; }
  else async = 0;

  pid = fork();
  if(pid == 0) { /* child process */
    execvp(args[0], args);
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
}

int main (int argc, char* argv [])
{
  char cmdline[BUFSIZ];
  
  for(;;) {
    printf("COP4338$ ");
    if(fgets(cmdline, BUFSIZ, stdin) == NULL) {
      perror("fgets failed");
      exit(1);
    }
    execute(cmdline) ;
  }
  return 0;
}
