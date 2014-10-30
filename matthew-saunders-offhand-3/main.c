#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF 1024

/**
 * This function uses two children processes to sort an ls using execlp()
 * by passing the output up to the parent process through pipes for 
 * output to stdout.
 */
int main(int argc, char* argv[]){

  /* variables */
  pid_t pid;		// process id - 0 if child process, not 0 if parent process
  int fd[2];		// file descriptor vector for piped file
  char buf[BUFF];	// buffer for reading data from files
  int n;

  /* create pipe */
  if(pipe(fd) < 0) { perror("pipe failed"); exit(-1); };

  pid = fork();
  if(pid < 0) { /* an error occurred */
    perror("fork failed");
    exit(-1);
  } else if(pid == 0) { /* child process */
    pid_t pid_B;            // process id - 0 if child process, not 0 if parent process
    int fd_B[2];            // file descriptor vector for piped file

    /* create pipe */
    if(pipe(fd_B) < 0) { perror("pipe-B failed"); exit(-1); };

    pid_B = fork();
    if(pid_B < 0) { /* an error occurred */
      perror("fork failed");
      exit(-1);
    } else if(pid_B == 0) { /* child process */
      /* update file descriptors */
      close(fd[0]);
      close(fd[1]);
      close(fd_B[0]);      
      dup2(fd_B[1],STDOUT_FILENO);

      execlp("/bin/ls", "ls", "-l", NULL);

      /* return only when exec fails */
      perror("exec failed");
      exit(-1);
    } else { /* parent process */
      /* update file descriptors */
      close(fd[0]);
      dup2(fd[1], STDOUT_FILENO);
      close(fd_B[1]);
      dup2(fd_B[0], STDIN_FILENO);
      
      wait(0);
      execlp("sort", "sort", NULL);

      /* return only when exec fails */
      perror("exec failed");
      exit(-1);
    }

  } else { /* parent process */
    wait(0);    

    /* update file descriptors */
    close(fd[1]);

    while((n = read(fd[0], buf, BUFSIZ)) > 0) {
      buf[n] = 0;
      printf("%s", buf);
    }

    close(fd[0]);
  }

  return 0;
}
