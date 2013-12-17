#include "httpclient.h"
 //open declared here
#define MAXBUF 5000
#define MAXBUFI 5000


/*
Following function parses the header ,finds the content length 
and returns it
*/
int findcontentlength(char*muffer)
{
char *point;
char length[100] = { 0 };
point=strstr(muffer,"Content-Length:")+strlen("Content-Length:");
unsigned int i;
for (i=0;i<strlen(point);i++)
{
	if(*(point+i)=='\r' && *(point+i+1)=='\n')
	break;
	length[i]=*(point+i);
}
int len=0;				
len=atoi(length);
return len;
}



// Pulls the file from the server

int pullfile(int k,const char *file,char* muffer, int sockfd)
{

int fd;
char *temp;
int bytes_read=1;
int bytes_write=1;
int total=0;
// count=0;

printf("Inside 200OK\n");		
//Parsing the Header	

//parsing and getting the length in payload of the file recieved by using the functin "content length"
int lenn=0;
lenn=findcontentlength(muffer);
		
printf("filesize...%d\n",lenn);	
fd = open(file, O_RDWR | O_CREAT | O_NONBLOCK |O_TRUNC, S_IRWXU);
if (fd < 0) 
	{                                
	printf("open local file error");
        return -1;
        }
//reaching till payload and temp contains the whole string						
temp=strstr(muffer,"\r\n\r\n")+strlen("\r\n\r\n");
if (write(fd, temp, strlen(temp)) !=(int) strlen(temp)) 
{
  	printf("partially write/Failed");
        return -1;
}
int u=0;
u=(int)strlen(temp);
printf("bytes_read.%d....total...%d..filesize.%d\n",bytes_read,total,lenn);

/******************************************************************
Recieving until there is not byte left from the server!		
Also matching the content length with the number of bytes
*****************************************************************/		
//while (( bytes_read > 0 ) && (total < (filesize)))
//sleep(8);

while (bytes_read!=0)
{
	//count++;
	printf("%s", muffer);			
		
		
	memset(muffer, '\0', MAXBUF);			
	bytes_read = recv(sockfd, muffer, sizeof(muffer), 0);
	printf("bytes_read %d....filesize%d....total...%d\n",bytes_read,lenn,total);	
	if(bytes_read==0)
	break;	

	bytes_write=write(fd,muffer,strlen(muffer));
//	printf("bytes_write....%d",bytes_write);
	total = bytes_read+total;
	memset(muffer, '\0', MAXBUF);
	if(total+u==lenn)
	break;		
	//if ( bytes_read > 0 )
	//	printf("%s", muffer);
	//memset(muffer, '\0', MAXBUF);
}
		
//printf("total bytes written%d and file size was %d....total%d.\n",total+u,lenn);
printf("strlen temp%d\n",u);

close(fd);
close(sockfd);
return 0;

}

//http get is responsible if client give get command in terminal
int http_get(const char *file , int sockfd)
{
char muffer[MAXBUF];
char muf[MAXBUFI];
int bytes_read;//bytes_count;
unsigned int rv;
bytes_read = 1;
unsigned int i;
int g=1;
//int fd;
//int count=0;

printf("Name of file %s\n",file);
/*Putting the HTTP GET header into the buffer
-------------------------|
|GET /filebname HTTP/1.1
|Iam: gillb1


|<BODY>
-------------------------|
*/
sprintf(muffer, "GET /%s HTTP/1.1\r\nIam: gill\r\n\r\n", file);	
rv = 0;
rv = send(sockfd, muffer, strlen(muffer), 0);
if (rv != strlen(muffer))
	printf("Error @ send\n");
else
	printf("OK\n");
/*---While there's data, read and print it---*/
memset(muffer, '\0', MAXBUF);
bytes_read = recv(sockfd, muffer, sizeof(muffer), 0);
printf("%s\n",muffer);	


char REQNO[20] = { 0 };		
char* temp=NULL;	


/*Parsing the response for checking whether server has got the file or not*/
temp=strstr(muffer,"HTTP")+strlen("HTTP/1.1 ");	
for(i=0;i<strlen(temp);i++)
	{
	//check for new line					
	if (*(temp+i)=='\r')
		break;
	REQNO[i]=*(temp+i);						
	}
//printf("REQNO contains%s....strlen(REQNO)%d....strlen(404 NOTOK)%d\n",REQNO,strlen(REQNO),strlen("404 NOTOK"));
/***************************************************
Following ifelse statements print the response from the
server either there is an error or success.It compares
the header with 200OK and 404NOT OK.
**************************************************/
if(strcmp(REQNO,"200 OK")==0)
	{
	int k=1;
	/*
	Calls the pull file function, which will ultimately pull 
	the whole file from the server
	*/
	k=pullfile(g,file,muffer,sockfd);
	if(k==0)
		{
		printf("200OK successfull");
		}
	}//end of strcmp 200 OK 	
	else if ((strcmp(REQNO,"404 Not Found"))==0)
	{
		printf("File not found at reciever side , 400NOTOK");
	}
	else
	{
	printf("neither 200OK nor 400NOTOK...it could be HTTP/1.0");
	}	

memset(muf, '\0', MAXBUFI);
return 0;
//memset(buffer, '\0', MAXBUF);	
}


