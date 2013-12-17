/*****************************************************************************/
/*** http dns-client.c                                                     ***/
/*** Bilal Shaukat Gill                                                    ***/
/*** Student Id:280244         						   ***/
/*****************************************************************************/
#include "httpclient.h"
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <errno.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<strings.h>
#include<climits>
#include<sstream>
#include<stdlib.h>
#include<fcntl.h> //open declared here
#include <iostream>
#include <string>
#include <unistd.h>
//#include<iostream>
using namespace std;



int main(int Count, char **Strings)
{
int rv,sockfd;
struct addrinfo hints;
struct addrinfo *res;
//ressave;
int n=1;
const char  *host_name,*server_port,*file_name;
rv = 0;
    /*---Make sure we have the right number of parameters---*/


if (Count!=3)
{	//testport <IP-addr> <FILENAME> <port> <GET=G/PUT=P> <p/np>

	printf("**********Please provide right format");
	printf("usage:./client <GET or PUT> <hostname>:<port>/<filename>\n");
	printf("usage<example>:./client GET nwprog1.netlab.hut.fi:3000/index\n");
}

string arg_b,arg1,hostname,path,port,filename;
size_t index,index2;

//indentifying GET or PUT method.
int idea=3;

arg_b=Strings[1];
if ((arg_b.compare("GET")==0)|| (arg_b.compare("Get")==0))
idea=1;
if ((arg_b.compare("PUT")==0)|| (arg_b.compare("Put")==0))
idea=2;
if ((arg_b.compare("POST")==0)|| (arg_b.compare("Post")==0))
idea=3;

printf("idea%d\n",idea);

//nwprog1.netlab.hut.fi:3000/
//identifying the path , port and file name
arg1=Strings[2];
index=arg1.find_first_of(":");
index2=arg1.find_first_of("/");
if(index!=string::npos){
hostname=arg1.substr(0,index);
port=arg1.substr(index);

}

port=arg1.substr(index+1,(index2-index-1));
filename=arg1.substr(index2+1);

host_name=hostname.c_str();
server_port=port.c_str();
file_name=filename.c_str();


    /*---Initialize server address/port struct---*/
//size_t out_size=sizeof(buffer);
bzero(&hints, sizeof(struct addrinfo));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype=SOCK_STREAM;
//Name Resolution Address and port 	
n=getaddrinfo(host_name,server_port, &hints, &res);
if (n!=0)
{
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(n));
        exit(EXIT_FAILURE);
}
else
{
	printf("getaddrinfo OK\n");
}
//ressave =res;

do{

	sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if (sockfd==-1)
	{
		printf("socket error\n");
	}
	else
	{
		printf("socket OK\n");
	}
/*---Connect to server---*/
rv = connect(sockfd,res->ai_addr,res->ai_addrlen);
if (rv == 0)
	printf("Connect Ok\n");
else
	printf("Connect error\n");
	break ; 

}while ((res=res->ai_next)!=NULL);

if (res==NULL)
	{
	printf("res=null error");
	}
int y=1;
std::string x = hostname;
if (idea==1)
{
  y=http_get(file_name,sockfd);
  if (y==0)
  printf("Http get success\n");
  else
  printf("Http get failure\n");
}
//Condition for the PUT header
else if (idea==2)
{
  
  y=http_put(file_name,sockfd,x.c_str());
  if (y==0)
  printf("Http put success\n");
  else
  printf("Http put failure\n");
}
else if (idea==3)
{ //file_name is infact the domain name for look up
   // Strings [3]is the query type
  y=http_post(file_name,sockfd,x.c_str(),Strings[3]);
  if(y==0)
  printf("Http post success");
  else 
  printf("Http post failure");

}
else
{
printf("Error:Write either G for GET and P for Put\n");
printf("%s\n\n",Strings[4]);
}

  /*---Clean up---*/
    close(sockfd);
   freeaddrinfo(res);
    return 0;
}




