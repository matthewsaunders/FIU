#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unistd.h>

#define Type_A 1 //ipv4
#define Type_NS 2 //nameserver

/*
DNS HEADER
                                1  1  1  1  1  1
  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                      ID                       |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|QR|  Opcode   |AA|TC|RD|RA|    Z   |   RCODE   |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                   QDCOUNT                     |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                   ANCOUNT                     |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                   NSCOUNT                     |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                   ARCOUNT                     |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
struct DNS_HEADER{
  unsigned id:16; // identification number
 
  unsigned rd :1; // recursion desired
  unsigned tc :1; // truncated message
  unsigned aa :1; // authoritive answer
  unsigned opcode :4; // purpose of message
  unsigned qr :1; // query/response flag
 
  unsigned rcode :4; // response code
  unsigned cd :1; // checking disabled
  unsigned ad :1; // authenticated data
  unsigned z :1; // its z! reserved
  unsigned ra :1; // recursion available
 
  unsigned qd_count:16; // number of question entries
  unsigned an_count:16; // number of answer entries
  unsigned ns_count:16; // number of authority entries
  unsigned ar_count:16; // number of resource entries
};


/*
DNS QUERY
			       1  1  1  1  1  1
 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 						|
/ 		     QNAME 			/
/ 						/
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		     QTYPE 			|
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		     QCLASS 			|
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
struct DNS_QUESTION {
  unsigned qtype:16;
  unsigned qclass:16;
};

struct DNS_QUERY {
  char *name;
  struct DNS_QUESTION *question;
};

/*
			       1  1  1  1  1  1
 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 						|
/ 						/
/ 		     NAME 			/
| 						|
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|	 	     TYPE 			|
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		     CLASS 			|
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		      TTL 			|
| 						|	
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		    RDLENGTH 			|
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
/ 		     RDATA 			/
/ 						/
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
struct R_DATA {
  unsigned type:16;
  unsigned class:16;
  unsigned ttl:32;
  unsigned rdlength:16;
};

struct RES_RECORD {
  char *name;
  struct R_DATA *resource;
  unsigned char *rdata;
};

void print_dns_servers()
{
  printf("\n\t\t-----------     DNS Servers     ----------\n");
  printf("a.root-servers.net	198.41.0.4, 2001:503:ba3e::2:30	VeriSign, Inc.\n");
  printf("b.root-servers.net	192.228.79.201, 2001:500:84::b	University of Southern California (ISI)\n");
  printf("c.root-servers.net	192.33.4.12, 2001:500:2::c	Cogent Communications\n");
  printf("d.root-servers.net	199.7.91.13, 2001:500:2d::d	University of Maryland\n");
  printf("e.root-servers.net	192.203.230.10	NASA (Ames Research Center)\n");
}

/*
void nametodnsformat(char *dns, char* host){
  printf(".... nametodnsformat\n");
  int lock=0 , i;
  printf("before -> %s\n", host);
  strcat(host,".");
  printf("after  -> %s\n", host);
  //printf("dns  -> %s\n", dns);

  for(i=0; i<strlen(host); i++){
    if(host[i]=='.'){
      *dns++ = i-lock;
      for(;lock<i;lock++){
        *dns++ = host[lock];
      }
      lock++;
    }
  }
  *dns++ = '\0';

  printf("----flag\n");

}
*/



void builddnsquery( char* host, char* buf ){

  printf(".... builddnsquery\n");
  char *qname; 
  struct DNS_HEADER *header; 
  
  header = (struct DNS_HEADER *)&buf;
  header->id = (unsigned short) htons(getpid());
  header->qr = 0;
  header->opcode = 0;
  header->aa = 0;  
  header->tc = 0;  
  header->rd = 1;  
  header->ra = 0;  
  header->z = 0;  
  header->ad = 0;  
  header->cd = 0;  
  header->rcode = 0;  
  header->qd_count = htons(1);  
  header->an_count = 0;  
  header->ns_count = 0;  
  header->ar_count = 0;  

  qname = (unsigned char*)&buf[sizeof(struct DNS_HEADER)];
  nametodnsformat(qname, host);
  
}

void processdnsresponse(){}


void gethostbyname(char *host, char *dns_server_ip){
  printf(".... gethostbyname\n");
  char buf[65536], *reader;
  int i, j, stop, s;

  //struct sockaddr_in a;
  struct sockaddr_in  dest;
  //struct RES_RECORD answer[20], auth[20], addit[20];
  //struct DNS_QUESTION *qinfo = NULL;
 
  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  dest.sin_family = AF_INET;
  dest.sin_port = htons(53);
  dest.sin_addr.s_addr = inet_addr(dns_server_ip);

  printf("\n------------------------------------------------------\n");
  printf("DNS server to query: %s\n", dns_server_ip);

  builddnsquery(host, buf);

}


int main (int argc, char* argv []){

  char dns_server_ip[100];
  char domain_name[100];

  if(argc != 3) {
    printf("Usage: %s [server_ip] [domain_name]\n", argv[0]);
    print_dns_servers();
    return 1;
  }

  strcpy(dns_server_ip, argv[1]);
  strcpy(domain_name, argv[2]);

  gethostbyname(domain_name, dns_server_ip);

  return 0;
}
