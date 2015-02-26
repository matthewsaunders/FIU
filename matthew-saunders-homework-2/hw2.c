/*
 Name:	Matthew Saunders
 Class:	COP 4520
 Date:	27 Feb 2015
 Summary:
*/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

/* This function is a collective operation; that is, it shall be called by all mpi processes or none at all. 
Each process is expected to provide a value 'x', and when the function returns, the process whose rank is 
'root' shall have to sum stored in the location pointed by 'sum'. */
void addall(int x, int* sum, int root);

/* This function is a collective operation; that is, it shall be called by all mpi processes or none at all. 
Each process is expected to provide a block of data of size 'sendcnt' stored in 'sendbuf'. When the function
returns, each process will have the data blocks sent from all other processes (including itself) stored in 
'recvbuf'. The receive buffer shall be allocated before hand with enough room to store data from all processes. 
The block of data from the i-th process is received by every process and placed in the i-th block of the 
receive buffer  'recvbuf'. You can assume that all processes provide the same 'sendcnt'. */
void collectall(char* sendbuf, int sendcnt, char* recvbuf);

/*
 Name: hob
 Description:
 A helper function to return a mask with the highest order bit set to one
*/
int hob (int num){
  if(!num)
    return 0;

  int mask = 1;

  while (num>>=1)
    mask <<= 1;
  return mask;
}

void addall(int x, int* sum, int root){
  int p, id;
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;	/* MPI status */

  int otherNode;
  int sentData = 0;
  int mask = hob(p);
  int *buf = (int*)malloc(1);
  *sum = x;

  while(!sentData){
    otherNode = id ^ mask;
    if(id & mask){ //true if value at mask position in p is a 1
      // send data
      //printf("s: p%d to p%d \n", id, otherNode);
      MPI_Send(sum, 1, MPI_INT, otherNode, 0, MPI_COMM_WORLD);
      sentData = 1;
    }else{
      if(otherNode <= p-1){
        // receive data
        MPI_Recv(buf, 1, MPI_INT, otherNode, 0, MPI_COMM_WORLD, &status);
        *sum += *buf;
	//printf("r: p%d from p%d, sum: %d, buf: %d \n",id, otherNode, *sum, *buf);
      }
      mask>>=1;
    }

    if(id == root && !mask){
      //printf("process %d done... sum=%d \n", root, *sum);
      sentData = 1;
    }
  }

  free(buf);
  return;
}

void collectall(char* sendbuf, int sendcnt, char* recvbuf){

  int p, id;
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;    /* MPI status */
  MPI_Request send_request;
  MPI_Request recv_request;

  int otherNode;
  int mask = hob(p) >> 1;
  int i, j;
  int blocksize = sendcnt;
  int send_offset = 0;
  int recv_offset = blocksize;

  for(; i < sendcnt; i++) {
    recvbuf[i] = sendbuf[i];
  }


  while(mask){
    otherNode = id ^ mask;

    for(i=0;i<sizeof(recvbuf);i++){
      printf("recvbuf[%d-%d]: %c\n",id,i,recvbuf[i]);
    }


    if(otherNode <= p-1){
      
      //non-blocking send
      MPI_Isend(recvbuf + send_offset, sendcnt, MPI_CHAR, otherNode, 0, MPI_COMM_WORLD, &send_request);
      //blocking recv
      MPI_Recv(recvbuf + recv_offset, sendcnt, MPI_CHAR, otherNode, 0, MPI_COMM_WORLD, &status);

      sendcnt = 2*sendcnt;      
      printf("%d sendcnt: %d\n",id,sendcnt);
      send_offset = recv_offset;
      recv_offset = 2*recv_offset;
    }else{
      printf("WOAH %d, %d\n",id,otherNode);
    }

    mask>>=1;
    //MPI_Wait(&send_request, MPI_STATUS_IGNORE);
    //MPI_Wait(&send_request, &status);
    //MPI_Wait(&recv_request, MPI_STATUS_IGNORE);
    //MPI_Wait(&recv_request, &status);
    MPI_Barrier(MPI_COMM_WORLD);
  }

    for(i=0;i<sizeof(recvbuf);i++){
      printf("recvbuf[%d-%d]: %c\n",id,i,recvbuf[i]);
    }

  return;
} 

int main( int argc, char *argv[]  ){

  int p, id;
  int sum;

  /* initialize mpi, and find out the rank (id) and the total number
     of processes (p) */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  addall(id, &sum, 0);
  if(id==0) printf("addall->%d\n", sum);
  
  char ch = 'A'+id;
  char* buf = (char*)malloc(p+1);
  collectall(&ch, 1, buf);
  buf[p] = '\0';
  if(id==2) printf("\n\n%d: %s\n\n\n", id, buf);

  free(buf);
  /* Finalize MPI */
  MPI_Finalize();
  return 0;
}


