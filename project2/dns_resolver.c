#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char dns_servers [10][100];

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
struct DNS_Header{
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
struct DNS_Query {
  unsigned qname:16;
  unsigned qtype:16;
  unsigned qclass:16;
};





void get_dns_servers()
{
    FILE *fp;
    char line[100] , *p;
    char index = 0;
    if((fp = fopen("/etc/resolv.conf" , "r")) == NULL)
    {
        printf("Failed opening /etc/resolv.conf file \n");
    }
     
    while(fgets(line , 100 , fp)){
        if(line[0] == '#'){
            continue;
        }
        if( !(strncmp(line , "nameserver" , 10)) )
        {
            p = strtok(line , " ");
            p = strtok(NULL , " ");

            //strcpy(dns_servers[index], p); 
            strcpy(dns_servers[0] , "208.67.222.222");
            printf("p: %s", dns_servers[index-1]);
        }
    }
}







int main (int argc, char* argv []){

  char server_ip[100];
  char domain_name[100];

  if(argc != 3) {
    printf("Usage: %s [server_ip] [domain_name]\n", argv[0]);
    return 1;
  }

  strcpy(server_ip, argv[1]);
  strcpy(domain_name, argv[2]);

  printf("server_ip: %s\n", server_ip);
  printf("domain_name: %s\n", domain_name);

  get_dns_servers();

  return 0;
}
