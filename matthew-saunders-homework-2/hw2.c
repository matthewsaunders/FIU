/*
 Name:	Matthew Saunders
 Class:	COP 4520
 Date:	27 Feb 2015
 Summary:
*/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <string.h>

void addall(int x, int* sum, int root);
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

/* This function is a collective operation; that is, it shall be called by all mpi processes or none at all. 
Each process is expected to provide a value 'x', and when the function returns, the process whose rank is 
'root' shall have to sum stored in the location pointed by 'sum'. */
void addall(int x, int* sum, int root){
  int p, id;
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;	/* MPI status */

  int otherNode; /* id of node to send/recv */
  int sentData = 0; /*1 if this node has sent its data */
  int mask = hob(p); /* set the bit mask for determining the otherNode */
  int *buf = (int*)malloc(1); /*create a buffer to send recieve data value */
  *sum = x;

  /* until this node has sent its data, determine if it should send or receive this loop iteration */
  while(!sentData){
    otherNode = id ^ mask;

    /* true if the bit of this node's id is 1 at the masks position */
    if(id & mask){
      // send data
      MPI_Send(sum, 1, MPI_INT, otherNode, 0, MPI_COMM_WORLD);
      sentData = 1;
    }else{
      /* true if otherNode exists within # processes */
      if(otherNode <= p-1){
        // receive data
        MPI_Recv(buf, 1, MPI_INT, otherNode, 0, MPI_COMM_WORLD, &status);
        *sum += *buf;
      }

      /* shift mask bit right one position */
      mask>>=1;
    }

    /* true if there is only one process */
    if(id == root && !mask){
      sentData = 1;
    }
  }

  free(buf);
  return;
}

/* This function is a collective operation; that is, it shall be called by all mpi processes or none at all. 
Each process is expected to provide a block of data of size 'sendcnt' stored in 'sendbuf'. When the function
returns, each process will have the data blocks sent from all other processes (including itself) stored in 
'recvbuf'. The receive buffer shall be allocated before hand with enough room to store data from all processes. 
The block of data from the i-th process is received by every process and placed in the i-th block of the 
receive buffer  'recvbuf'. You can assume that all processes provide the same 'sendcnt'. */
void collectall(char* sendbuf, int sendcnt, char* recvbuf){

  int p, id; 
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Status status;    /* MPI status */

  int otherNode; /* id of node to send/recv */
  int mask = hob(p); /* set the bit mask for determining the otherNode */
  int i; /* general loop iterator */
  int recv_offset = sendcnt; /* offset into the recvbuf array to place new data */

  /* initialize the recvbuf with this nodes startng data */
  for(i=0; i < sendcnt; i++) {
    recvbuf[i] = sendbuf[i];
  }

  /* true while the data mask has value greater than 0, false once all binary data positions have been looped through */
  while(mask){
    otherNode = id ^ mask;

    if(otherNode <= p-1){
      
      /* Send the data this node has from the recvbuf starting at the begininng of the array until 
         the sendcnt amount */
      MPI_Send(recvbuf, sendcnt, MPI_CHAR, otherNode, 0, MPI_COMM_WORLD);
      /* Receive data should be placed in recvbuf starting at sendcnt, the position of the first unused 
         data location. */
      MPI_Recv(recvbuf + recv_offset, sendcnt, MPI_CHAR, otherNode, 0, MPI_COMM_WORLD, &status);

      /* double the sendcnt and update the position to insert data in the recvbuf */
      sendcnt = 2*sendcnt;      
      recv_offset = 2*recv_offset;
    }

    mask>>=1;
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
  char* buf = (char*)malloc((p+1)*sizeof(char));
  collectall(&ch, 1, buf);
  buf[p] = '\0';
  if(id==2) printf("%d: %s\n", id, buf);

  free(buf);
  /* Finalize MPI */
  MPI_Finalize();
  return 0;
}


