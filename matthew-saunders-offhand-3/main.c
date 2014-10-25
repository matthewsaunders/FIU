#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF 1024

int main(int argc, char* argv[]){

  /* variables */
  pid_t pid;		// process id - 0 if child process, not 0 if parent process
  int fd[2];		// file descriptor vector for piped file
  char buf[BUFF];	// buffer for reading data from files
  int n;

  /* create pipe */
  if(pipe(fd) < 0) { perror("pipe failed"); exit(-1); };

  /* fork process - fork 1*/
  pid = fork();
  if(pid < 0) { /* an error occurred */
    perror("fork failed");
    exit(-1);
  } else if(pid == 0) { /* child process */
    printf("CHILD PROCESS FOUND\n");

    /* close unused file descriptors */
    close(fd[0]);
    //dup2(STDOUT_FILENO, fd[1]);
    dup2(fd[1], STDOUT_FILENO);

    /* run command */
    execlp("/bin/ls", "ls", "-l", NULL);
    
    /* return only when exec fails */
    perror("exec failed");
    exit(-1);
      //create pipe 2
      /* fork process - fork 2*/
      
      //if child process, exec ls
      // pass output to pipe 

      //wait for child
      //read from pipe with child for input
      //exec sort of input
      //pass output to parent

  } else { /* parent process */
    wait(0);    
    printf("PARENT PROCESS FOUND\n");

    /* close unused file descriptors */
    close(fd[1]);

    while((n = read(fd[0], buf, BUFSIZ)) > 0) {
      buf[n] = 0;
      printf("%s", buf);
    }

    // wait for children
    //print input from fork to stdout

    close(fd[0]);

  }

  return 0;
}
