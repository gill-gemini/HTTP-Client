
#ifndef HTTPCLIENT_H //Guard for double inclusion 
#define HTTPCLIENT_H

#include<stdio.h>
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
#include<fcntl.h>
#include<sys/stat.h>
/* Http get function used for obtaining the files from the server */
int http_get(const char * file,int sockfd);
/*
 * Http put is used for the placing the file onto the server
 */
int http_put(const char * file, int sockfd , const char * dns);

/*
HTTP Post Method for look up of domain names
*/
int http_post(const char * lookup, int sockfd, const char *dns, const char *type);

/* Parses the header and finds the content length of the file*/
int findcontentlength(char *muffer);

/* Pulls the file from the server and copies the data in the desired file*/
int pullfile(int k,const char *file,char* muffer, int sockfd);

/* Pushes the file from the client to the server to in HTTP PUT function*/
int pushfile(int sockfd,char *buffer, FILE*fp,int h);
#endif

