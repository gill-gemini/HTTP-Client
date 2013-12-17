#include "httpclient.h"


#define MAXBUF 5000
#define MAXBUFI 5000

// Pushes the file towards server, until the bytes sent is equal to contentlength
int pushfile(int sockfd,char *buffer, FILE*fp,int h)
{
	int bytes_read=1;
	int bytes_write = 1;
	int total = 0;
//	FILE
while(bytes_write>0)
	 {
	    // Read data into buffer.  We may not have enough to fill up buffer, so we
	    // store how many bytes were actually read in bytes_read.
	    bytes_read = fread(buffer, sizeof(char), MAXBUF, fp);
	  
	    total = bytes_read + total;
	    if (bytes_read == 0) // We're done reading from the file
	    	break;
 
	  if (bytes_read < 0) {
	        printf("Error in Byte_Read");// handle errors
		return 1;
	    }
	  if ((bytes_write = write(sockfd, buffer, bytes_read)) < 0) 
	    {
	    	printf("Error during writing!\n");
	    	return 1;
	   }
	//if  bytes sent is equal to contentlength then break 	
	 if(total==h)
	   break;
	memset(buffer, '\0', MAXBUF);
	 }

return 0;

}



// This function is responsible for file status check and putting the file to the server
int http_put(const char *file , int sockfd ,const char *dns)
{
	char buffer[MAXBUF];
	unsigned int rv;
	FILE*fp;
	struct stat fileStat;
	std::string fname = file;
	printf("%s", fname.c_str());

	fp=fopen(fname.c_str(),"r");
	
	if(stat(file,&fileStat)<0)
	{
	printf("there is no file titled %s or there is no acess to read",file);
	return 1;	
	}
	
	 memset(buffer, '\0', MAXBUF);	
	/*Putting the HTTP PUT header into the buffer
-------------------------|
|PUT /filename HTTP/1.1
|Host:
|Content-Type:text/plain
|Iam: gill1
|Content-Length:


|<BODY>
-------------------------|
*/
	sprintf(buffer, "PUT /%s HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\nIam:gill\r\nContent-Length: %d\r\n\r\n", file, dns,(int)fileStat.st_size);
	//nwprog1.netlab.hut.fi:8934
	rv = 0;
		rv = send(sockfd, buffer, strlen(buffer), 0);
		if (rv != strlen(buffer))
			printf("Error @ send\n");
		else
			printf("OK at send\n");

		 memset(buffer, '\0', MAXBUF);


	
	
	
	int j=0;
	int h=0;
	h=(int)fileStat.st_size;
	j=pushfile(sockfd, buffer,fp,h);
	if (j==0)
	{
	printf("push file success");
	}

	  
close(sockfd);
//close(fp);
return 0;
}
