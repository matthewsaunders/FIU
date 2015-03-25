#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>



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

void nametodnsformat(){

}


void builddnsquery(){}
void senddnsquery(){}

void printdnsresponse(){}
void processdnsresponse(){}
void recvdnsresponse(){}











void gethostbyname(char *host){
  //unsigned char buf[65536], *qname, *reader;
  int i, j, stop, s;

  struct sockaddr_in a;
  struct sockaddr_in  dest;
  //struct Res_Record answer[20], auth[20], addit[20];

  struct DNS_HEADER *dns = NULL;
  //struct Question *qinfo = NULL;
 
  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


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

  printf("dns_server_ip: %s\n", dns_server_ip);
  printf("domain_name: %s\n", domain_name);

  gethostbyname(domain_name);

  return 0;
}
