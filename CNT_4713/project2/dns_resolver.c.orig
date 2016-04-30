/**
 *
 *
 *
 */
//Libraries
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<stdlib.h>    //malloc
#include<sys/socket.h>    //you know what this is for
#include<arpa/inet.h> //inet_addr , inet_ntoa , ntohs etc
#include<netinet/in.h>
#include<unistd.h>    //getpid
 
//Macros
#define Type_A 1 //Ipv4 address
#define Type_NS 2 //Nameserver
#define T_CNAME 5
 
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
struct DNS_HEADER
{
    unsigned short id; // identification number
 
    unsigned char rd :1; // recursion desired
    unsigned char tc :1; // truncated message
    unsigned char aa :1; // authoritive answer
    unsigned char opcode :4; // purpose of message
    unsigned char qr :1; // query/response flag
 
    unsigned char rcode :4; // response code
    unsigned char cd :1; // checking disabled
    unsigned char ad :1; // authenticated data
    unsigned char z :1; // its z! reserved
    unsigned char ra :1; // recursion available
 
    unsigned short q_count; // number of question entries
    unsigned short ans_count; // number of answer entries
    unsigned short auth_count; // number of authority entries
    unsigned short add_count; // number of resource entries
};
 
/*
DNS QUERY
			                   1  1  1  1  1  1
 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 						                        |
/ 		     QNAME 			                    /
/ 						                        /
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		     QTYPE 			                    |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		     QCLASS 			                |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
struct QUESTION
{
    unsigned short qtype;
    unsigned short qclass;
};

typedef struct
{
    unsigned char *name;
    struct QUESTION *ques;
} QUERY;
 
/*
DNS RESPONSE
			                   1  1  1  1  1  1
 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 						                        |
/ 						                        /
/ 		     NAME 			                    /
| 						                        |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|	 	     TYPE 			                    |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		     CLASS 			                    |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		      TTL 			                    |
| 						                        |	
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
| 		    RDLENGTH 			                |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
/ 		     RDATA 			                    /
/ 						                        /
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*/
#pragma pack(push, 1)
struct R_DATA
{
    unsigned short type;
    unsigned short _class;
    unsigned int ttl;
    unsigned short data_len;
};
#pragma pack(pop)
 
struct RES_RECORD
{
    unsigned char *name;
    struct R_DATA *resource;
    unsigned char *rdata;
};

//Variables
char dns_server_ip[100];
unsigned char hostname[100];
unsigned char buf[65536],*qname,*reader;
int pointer, s;
 
struct sockaddr_in a;
struct sockaddr_in dest;
struct RES_RECORD answers[20],auth[20],addit[20]; //the replies from the DNS server
struct DNS_HEADER *header = NULL;
struct QUESTION *qinfo = NULL;

//Function Prototypes
void getIpOfHostname (unsigned char* , int);
void nameToDnsFormat (unsigned char*,unsigned char*);
unsigned char* ReadName (unsigned char*,unsigned char*,int*);
void printRootDnsServers ();
void processAnswerRecords();
void processAuthoritiesRecords();
void processAdditionalRecords();

/**
 *
 */
int main(int argc , char *argv[]){
  //Check number of command line arguments
  if(argc != 3) {
    printf("Usage: %s [server_ip] [domain_name]\n", argv[0]);
    printRootDnsServers();
    return 1;
  }
   
  //Copy command line args to variables
  strcpy(dns_server_ip, argv[1]);
  strcpy(hostname, argv[2]);
   
  //Query DNS server for host IP
  getIpOfHostname(hostname , Type_A);
 
  return 0;
}
 
/**
 * Perform a DNS query by sending a packet
 */
void getIpOfHostname(unsigned char *host , int query_type)
{
  int i;
	
  printf("\n---------------------------------------\n");
  printf("DNS server to query: %s\n" , dns_server_ip);
 
  //Create a UDP socket
  s = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP); 
 
  dest.sin_family = AF_INET;
  dest.sin_port = htons(53);
  dest.sin_addr.s_addr = inet_addr(dns_server_ip); //dns servers
 
  //Set the DNS header
  header = (struct DNS_HEADER *)&buf;
  header->id = (unsigned short) htons(getpid());
  header->qr = 0; //This is a query
  header->opcode = 0; //This is a standard query
  header->aa = 0; //Not Authoritative
  header->tc = 0; //This message is not truncated
  header->rd = 1; //Recursion Desired
  header->ra = 0; //Recursion not available! hey we dont have it (lol)
  header->z = 0;
  header->ad = 0;
  header->cd = 0;
  header->rcode = 0;
  header->q_count = htons(1); //we have only 1 question
  header->ans_count = 0;
  header->auth_count = 0;
  header->add_count = 0;
 
  //point to the query portion
  qname =(unsigned char*)&buf[sizeof(struct DNS_HEADER)];
 
  nameToDnsFormat(qname, host);
  qinfo =(struct QUESTION*)&buf[sizeof(struct DNS_HEADER) + (strlen((const char*)qname) + 1)]; //fill it
 
  qinfo->qtype = htons( query_type ); //type of the query , A , MX , CNAME , NS etc
  qinfo->qclass = htons(1); //its internet (lol)
 
  size_t queryLength = sizeof(struct DNS_HEADER) + (strlen((const char*)qname)+1) + sizeof(struct QUESTION);
    
  //Send DNS query
  if( sendto(s,(char*)buf,queryLength,0,(struct sockaddr*)&dest,sizeof(dest)) < 0){
    perror("Failed to send DNS Query.\n");
  }
     
  //Receive DNS response
  i = sizeof dest;
  if(recvfrom (s,(char*)buf , 65536 , 0 , (struct sockaddr*)&dest , (socklen_t*)&i ) < 0){
    perror("Failed to receive DNS Response.\n");
  }
   
  header = (struct DNS_HEADER*) buf;  //set postion of DNS header
  reader = &buf[sizeof(struct DNS_HEADER) + (strlen((const char*)qname)+1) + sizeof(struct QUESTION)]; //move reader to response section
 
  //print DNS response section counts
  printf("Reply received. Content overview: \n");
  printf("\t%d Answers.\n",ntohs(header->ans_count));
  printf("\t%d Intermediate Name Servers.\n",ntohs(header->auth_count));
  printf("\t%d Additional Information Records.\n",ntohs(header->add_count));
 
  //Start reading answers
  pointer=0;
 
  //process and print the DNS response by sections
  processAnswerRecords();
  processAuthoritiesRecords();
  processAdditionalRecords();

  //if there is no answer, query an intermediate dns server
  if(ntohs(header->ans_count) < 1){
    long *p;
    p=(long*)addit[0].rdata;
    a.sin_addr.s_addr=(*p);
    strcpy(dns_server_ip,inet_ntoa(a.sin_addr));
  
    getIpOfHostname(host, Type_A);			
  }
}

/**
 *
 */
void processAnswerRecords(){
  int i, j;
    
  for(i=0;i<ntohs(header->ans_count);i++){
    answers[i].name=ReadName(reader,buf,&pointer);
    reader = reader + pointer;
 
    answers[i].resource = (struct R_DATA*)(reader);
    reader = reader + sizeof(struct R_DATA);
 
    if(ntohs(answers[i].resource->type) == 1){ //ipv4
      answers[i].rdata = (unsigned char*)malloc(ntohs(answers[i].resource->data_len));
 
      for(j=0 ; j<ntohs(answers[i].resource->data_len) ; j++){
        answers[i].rdata[j]=reader[j];
      }
 
      answers[i].rdata[ntohs(answers[i].resource->data_len)] = '\0';
 
      reader = reader + ntohs(answers[i].resource->data_len);
    }else{ //not ipv4
      answers[i].rdata = ReadName(reader,buf,&pointer);
      reader = reader + pointer;
    }
  }
    
  //print DNS answer records
  printf("Answer Records : %d \n" , ntohs(header->ans_count) );
  for(i=0 ; i < ntohs(header->ans_count) ; i++){
    printf("\tName : %s ",answers[i].name);
 
    if( ntohs(answers[i].resource->type) == Type_A){ //IPv4 address
      long *p;
      p=(long*)answers[i].rdata;
      a.sin_addr.s_addr=(*p); //working without ntohl
      printf("\tIP: %s",inet_ntoa(a.sin_addr));
    }
         
    if(ntohs(answers[i].resource->type)==5){
      //Canonical name for an alias
      printf("\tName Server: %s",answers[i].rdata);
    }
    printf("\n");
  }
}


void processAuthoritiesRecords(){
  int i;
    
  //read authorities
  for(i=0;i<ntohs(header->auth_count);i++){
    auth[i].name=ReadName(reader,buf,&pointer);
    reader+=pointer;
 
    auth[i].resource=(struct R_DATA*)(reader);
    reader+=sizeof(struct R_DATA);
 
    auth[i].rdata=ReadName(reader,buf,&pointer);
    reader+=pointer;
  }
    
  //print DNS authorities records
  printf("Authoritive Records : %d \n" , ntohs(header->auth_count) );
  for( i=0 ; i < ntohs(header->auth_count) ; i++){
         
    printf("\tName : %s ",auth[i].name);
    if(ntohs(auth[i].resource->type)==Type_NS){
      printf("\tName Server: %s",auth[i].rdata);
    }
    printf("\n");
  }
}

void processAdditionalRecords(){
  int i, j;

  for(i=0;i<ntohs(header->add_count);i++){
    addit[i].name=ReadName(reader,buf,&pointer);
    reader+=pointer;
 
    addit[i].resource=(struct R_DATA*)(reader);
    reader+=sizeof(struct R_DATA);
 
    if(ntohs(addit[i].resource->type)==1){
      addit[i].rdata = (unsigned char*)malloc(ntohs(addit[i].resource->data_len));
	  for(j=0;j<ntohs(addit[i].resource->data_len);j++){
        addit[i].rdata[j]=reader[j];
	  }
      
	  addit[i].rdata[ntohs(addit[i].resource->data_len)]='\0';
      reader+=ntohs(addit[i].resource->data_len);
    }else{
      addit[i].rdata=ReadName(reader,buf,&pointer);
      reader+=pointer;
    }
  }

  //print DNS additional resource records
  printf("Additional Records : %d \n" , ntohs(header->add_count) );
  for(i=0; i < ntohs(header->add_count) ; i++){
    printf("\tName : %s ",addit[i].name);
    if(ntohs(addit[i].resource->type)==1){
      long *p;
      p=(long*)addit[i].rdata;
      a.sin_addr.s_addr=(*p);
      printf("\tIP : %s",inet_ntoa(a.sin_addr));
    }
    printf("\n");
  }
}

/*
 * 
 * */
u_char* ReadName(unsigned char* reader,unsigned char* buffer,int* count)
{
  unsigned char *name;
  unsigned int p=0,jumped=0,offset;
  int i , j;
 
  *count = 1;
  name = (unsigned char*)malloc(256);
 
  name[0]='\0';
 
  //read the names in 3www6google3com format
  while(*reader!=0){
    if(*reader>=192){
      offset = (*reader)*256 + *(reader+1) - 49152; //49152 = 11000000 00000000
      reader = buffer + offset - 1;
      jumped = 1; //we have jumped to another location so counting wont go up!
    }else{
      name[p++]=*reader;
    }
 
    reader++;
 
    if(jumped==0){
      *count += 1; //if we havent jumped to another location then we can count up
    }
  }
 
  name[p]='\0'; //string complete
  if(jumped==1){
    *count += 1; //number of steps we actually moved forward in the packet
  }
 
  //now convert 3www6google3com0 to www.google.com
  for(i=0;i<(int)strlen((const char*)name);i++){
    p=name[i];
    for(j=0;j<(int)p;j++){
      name[i]=name[i+1];
      i++;
    }
    name[i]='.';
  }
  name[i-1]='\0'; //remove the last dot
  return name;
}
 
/**
 *
 *
 */
void nameToDnsFormat(unsigned char* header,unsigned char* host){
  int lock = 0 , i;
  strcat((char*)host,".");
     
  for(i=0; i<strlen((char*)host); i++){
    if(host[i]=='.'){
      *header++ = i-lock;
      for(;lock<i;lock++){
        *header++=host[lock];
      }
      lock++;
    }
  }
  *header++='\0';
}

void printRootDnsServers(){
  printf("\n\t\t-----------     DNS Servers     ----------\n");
  printf("a.root-servers.net	198.41.0.4, 2001:503:ba3e::2:30	VeriSign, Inc.\n");
  printf("b.root-servers.net	192.228.79.201, 2001:500:84::b	University of Southern California (ISI)\n");
  printf("c.root-servers.net	192.33.4.12, 2001:500:2::c	Cogent Communications\n");
  printf("d.root-servers.net	199.7.91.13, 2001:500:2d::d	University of Maryland\n");
  printf("e.root-servers.net	192.203.230.10	NASA (Ames Research Center)\n");
}
