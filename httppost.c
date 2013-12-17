
#include "httpclient.h"
#define MAXBUF 5000

//Http_post is responsible for the put characteristic of http protocol
int http_post(const char * file, int sockfd, const char *dns, const char* type)
{
   char muffer[MAXBUF];
   char buffer[MAXBUF];
   sprintf(muffer,"Name=%s&Type=%s",file,type);
   int n=0;
   int bytes_read;
   n=strlen(muffer);
   printf("\nlength=%d\n",n);
   /*HTTP Post Header as defined in the slides Lecture 8 Network Programming                        */
   sprintf(buffer, "POST /dns-query HTTP/1.1\r\nHost: %s\r\nContent-Type: application/x-www-form-urlencoded\r\nIam:gill\r\nContent-Length: %d\r\n\r\nName=%s&Type=%s", dns,n,file,type);

   printf("%s",buffer);
   int rv = 0;
   rv = send(sockfd, buffer, strlen(buffer), 0);
   if (rv != (int)strlen(buffer))
   printf("Error @ send\n");
   else
   printf("\nOK at send\n");
   memset(buffer, '\0', MAXBUF);

   char REQNO[20] = { 0 };		
   char* temp=NULL;	
   bytes_read = recv(sockfd, muffer, sizeof(muffer), 0);
   printf("%s\n",muffer);

//printf("buffer contains%s\n",buffer);
temp=strstr(muffer,"HTTP")+strlen("HTTP/1.1 ");	
unsigned int i;
//int fd;	
for(i=0;i<strlen(temp);i++)
	{
	//check for new line					
	if (*(temp+i)=='\r')
		break;
	REQNO[i]=*(temp+i);						
	}

if(strcmp(REQNO,"200 OK")==0)
	{
	int k=1;
	
	//Calls the pull file function which is defined in httpget.c
	pullfile(k,"results.txt",muffer, sockfd);
	if(k==0)
		{
		printf("\n200OK successfull");
		}
	}//end of strcmp 200 OK 	
	else if ((strcmp(REQNO,"404 Not Found"))==0)
	{
		printf("\nFile not found at reciever side , 400NOTOK");
	}
	else
	{
	printf("\nneither 200OK nor 400NOTOK...it could be HTTP/1.0");
	}	



return 0;
}
